TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -L/usr/lib -lSDL2 -ldl -lpthread
LIBS += -L/usr/lib -lSDL2_image

SOURCES += \
        collision.cpp \
        ecs/controllersystem.cpp \
        ecs/rendersystem.cpp \
        game.cpp \
        main.cpp \
        map.cpp \
        vector2d.cpp

HEADERS += \
    animation.h \
    collision.h \
    ecs/components.h \
    ecs/controllersystem.h \
    ecs/ecs.h \
    ecs/pathfindsystem.h \
    ecs/rendersystem.h \
    ecs/systems.h \
    game.h \
    map.h \
    vector2d.h
