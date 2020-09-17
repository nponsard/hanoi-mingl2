/*
    @file: main.cpp
    @brief : point d'entrée du jeu
*/

#include "MinGL2_IUT_AIX/graphics/rgbacolor.h"
#include "MinGL2_IUT_AIX/graphics/vec2d.h"
#include "MinGL2_IUT_AIX/mingl.h"
#include "MinGL2_IUT_AIX/shape/rectangle.h"
/*#include "figs/rectangle.h"
#include "MinGL2_IUT_AIX/shape/triangle.h"
#include "figs/circle.h"
#include "figs/figure.h"*/
#include <chrono>
#include <iomanip>
#include <iostream>
#include <thread>
#include <utility>

#define WIDTH 1800
#define HEIGHT 1000

#define FRAME_DELAY 10 // temps entre deux mouvements, en millisecondes 

#define TEXT true // if true the text version is sent to the standard C++ output

using namespace std;

const unsigned Size(10); // le nombre de "palets"

MinGL Window("jeu", nsGraphics::Vec2D(WIDTH, HEIGHT), nsGraphics::KGreen);

typedef vector<unsigned> tower;
tower Tleft(Size);
tower Tmid(0);
tower Tright(0);
unsigned compteur(0);

void initCroissant(tower &tour) {
  for (unsigned i = 0; i < tour.size(); ++i) {
    tour[i] = tour.size() - i;
  }
}
const unsigned largeurPilier(10);
const unsigned Xplot1(WIDTH / 4 - largeurPilier / 2);
const unsigned Xplot2(2 * WIDTH / 4 - largeurPilier / 2);
const unsigned Xplot3(3 * WIDTH / 4 - largeurPilier / 2);
const unsigned paletHeight(HEIGHT / Tleft.size() - 1);
const unsigned pasPalet = (Xplot1 / 2) / (Tleft.size());

void drawHanoi2() {
  cout << "déplacement " << compteur << endl;
  cout << Tleft.size() << Tmid.size() << Tright.size() << endl;
  ++compteur;
  cout << "-";
  for (const unsigned &i : Tleft) {
    cout << setw(4) << i;
  }
  cout << endl;
  cout << "-";

  for (const unsigned &i : Tmid) {
    cout << setw(4) << i;
  }
  cout << endl;
  cout << "-";

  for (const unsigned &i : Tright) {
    cout << setw(4) << i;
  }
  cout << endl;
}
void drawHanoi() {

  if (TEXT)
    drawHanoi2();
  Window.clearScreen();

  unsigned y(HEIGHT);
  for (const unsigned i : Tleft) {
    Window << nsShape::Rectangle({Xplot1 - i * pasPalet, y - paletHeight},
                                 {Xplot1 + largeurPilier + i * pasPalet, y},
                                 nsGraphics::KRed);
    y -= paletHeight;
    cout << i << endl;
  }
  y = HEIGHT;
  for (const unsigned i : Tmid) {
    Window << nsShape::Rectangle({Xplot2 - i * pasPalet, y - paletHeight},
                                 {Xplot2 + largeurPilier + i * pasPalet, y},
                                 nsGraphics::KRed);
    y -= paletHeight;
  }
  y = HEIGHT;
  for (const unsigned i : Tright) {
    Window << nsShape::Rectangle({Xplot3 - i * pasPalet, y - paletHeight},
                                 {Xplot3 + largeurPilier + i * pasPalet, y},
                                 nsGraphics::KRed);
    y -= paletHeight;
    cout << i << endl;
  }
  Window << nsShape::Rectangle({Xplot1, 0}, {Xplot1 + largeurPilier, HEIGHT},
                               nsGraphics::KBlack);
  Window << nsShape::Rectangle({Xplot2, 0}, {Xplot2 + largeurPilier, HEIGHT},
                               nsGraphics::KBlack);
  Window << nsShape::Rectangle({Xplot3, 0}, {Xplot3 + largeurPilier, HEIGHT},
                               nsGraphics::KBlack);
  Window.finishFrame();

  std::this_thread::sleep_for(std::chrono::milliseconds(FRAME_DELAY));
}

void deplacementHanoi(tower &TEntree, tower &TSortie) {

  unsigned temp(TEntree.back());
  TEntree.pop_back();
  TSortie.push_back(temp);
}

void hanoi(unsigned n, tower &TOrigin, tower &TOut, tower &Tmid) {
  if (n > 0) {
    hanoi(n - 1, TOrigin, Tmid, TOut);
    deplacementHanoi(TOrigin, TOut);
    drawHanoi();
    hanoi(n - 1, Tmid, TOut, TOrigin);
  }
}

int main() {
  initCroissant(Tleft);

  Window.initGlut();
  Window.initGraphic();
  bool boucle(true);

  drawHanoi();
  hanoi(Tleft.size(), Tleft, Tright, Tmid);
  std::this_thread::sleep_for(std::chrono::seconds(4));

  return 0;
}
