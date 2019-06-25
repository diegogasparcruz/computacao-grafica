TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += bib
INCLUDEPATH += gui_glut
INCLUDEPATH += pessoal

LIBS += -lGL -lGLU -lglut -l3ds -lSDL_image

SOURCES += main.cpp \
    bib/Camera.cpp \
    bib/CameraDistante.cpp \
    bib/CameraJogo.cpp \
    bib/Desenha.cpp \
    bib/model3ds.cpp \
    bib/Vetor3D.cpp \
    gui_glut/extra.cpp \
    gui_glut/gui.cpp \
    pessoal/objeto.cpp \
    pessoal/bus.cpp \
    pessoal/banco.cpp \
    pessoal/plaza.cpp \
    pessoal/pessoa.cpp \
    pessoal/sol.cpp \
    pessoal/statue.cpp \
    pessoal/tree.cpp \
    pessoal/home.cpp \
    pessoal/parede.cpp

HEADERS += \
    bib/Camera.h \
    bib/CameraDistante.h \
    bib/CameraJogo.h \
    bib/Desenha.h \
    bib/model3ds.h \
    bib/Vetor3D.h \
    gui_glut/extra.h \
    gui_glut/gui.h \
    pessoal/objeto.h \
    pessoal/bus.h \
    pessoal/banco.h \
    pessoal/plaza.h \
    pessoal/pessoa.h \
    pessoal/sol.h \
    pessoal/statue.h \
    pessoal/tree.h \
    pessoal/home.h \
    pessoal/parede.h
