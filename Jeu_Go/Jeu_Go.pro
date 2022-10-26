TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Goban.cpp \
        Joueur.cpp \
        Piece.cpp \
        main.cpp

HEADERS += \
    Goban.h \
    Joueur.h \
    Piece.h
