TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

include(MinGL2_IUT_AIX/mingl.pri)

SOURCES += main.cpp \

QT += opengl core gui

#LIBS +=  -lglut -lGLU -lGL -lGLEW
LIBS +=  -lglut -lGLU -lGL

#INCLUDEPATH += /opt/local/include/GL/
INCLUDEPATH += /usr/include/GL/

QMAKE_CXXFLAGS += -Wall

