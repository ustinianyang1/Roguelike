QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    enemy.cpp \
    main.cpp \
    mainwindow.cpp \
    player.cpp

HEADERS += \
    enemy.h \
    mainwindow.h \
    player.h \
    settings.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    start.qrc

DISTFILES += \
    build/Slime/parts/Walk (jump)/Mini (1).png \
    build/Slime/parts/Walk (jump)/Mini (1).png \
    build/Slime/parts/Walk (jump)/Mini (2).png \
    build/Slime/parts/Walk (jump)/Mini (2).png \
    build/Slime/parts/Walk (jump)/Mini (3).png \
    build/Slime/parts/Walk (jump)/Mini (3).png \
    build/Slime/parts/Walk (jump)/Mini (4).png \
    build/Slime/parts/Walk (jump)/Mini (4).png \
    build/Slime/parts/Walk (jump)/Mini (5).png \
    build/Slime/parts/Walk (jump)/Mini (5).png \
    build/Slime/parts/Walk (jump)/large (1).png \
    build/Slime/parts/Walk (jump)/large (1).png \
    build/Slime/parts/Walk (jump)/large (1).png \
    build/Slime/parts/Walk (jump)/large (2).png \
    build/Slime/parts/Walk (jump)/large (2).png \
    build/Slime/parts/Walk (jump)/large (2).png \
    build/Slime/parts/Walk (jump)/large (3).png \
    build/Slime/parts/Walk (jump)/large (3).png \
    build/Slime/parts/Walk (jump)/large (3).png \
    build/Slime/parts/Walk (jump)/large (4).png \
    build/Slime/parts/Walk (jump)/large (4).png \
    build/Slime/parts/Walk (jump)/large (4).png \
    build/Slime/parts/Walk (jump)/large (5).png \
    build/Slime/parts/Walk (jump)/large (5).png \
    build/Slime/parts/Walk (jump)/large (5).png \
    build/Slime/parts/Walk (jump)/medium (1).png \
    build/Slime/parts/Walk (jump)/medium (1).png \
    build/Slime/parts/Walk (jump)/medium (2).png \
    build/Slime/parts/Walk (jump)/medium (2).png \
    build/Slime/parts/Walk (jump)/medium (3).png \
    build/Slime/parts/Walk (jump)/medium (3).png \
    build/Slime/parts/Walk (jump)/medium (4).png \
    build/Slime/parts/Walk (jump)/medium (4).png \
    build/Slime/parts/Walk (jump)/medium (5).png \
    build/Slime/parts/Walk (jump)/medium (5).png
