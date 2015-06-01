#-------------------------------------------------
#
# Project created by QtCreator 2013-01-01T12:52:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FancyLandEditor
TEMPLATE = app

include(readerwriter/readerwriter.pri)
include(file/file.pri)
include(datatype/datatype.pri)
include(tools/tools.pri)

SOURCES += main.cpp\
        mainwindow.cpp \
    EditScene.cpp \
    EditTool.cpp \
    Player.cpp \
    PlayerGraphicsItem.cpp \
    EnemyGraphicsItem.cpp \
    LayerEditScene.cpp \
    Palette.cpp \
    Workspace.cpp \
    Sprite.cpp \
    Dialog.cpp \
    ImportMenu.cpp \
    FileMenu.cpp \
    LayerEditWidget.cpp \
    LayerSpeedControlWidget.cpp \
    BorderGraphicsPixmapItem.cpp \
    Settings.cpp \
    SettingsDialog.cpp \
    ColorPushButton.cpp

HEADERS  += mainwindow.h \
    EditScene.h \
    EditTool.h \
    Player.h \
    PlayerGraphicsItem.h \
    EnemyGraphicsItem.h \
    LayerEditScene.h \
    Palette.h \
    Workspace.h \
    Sprite.h \
    Dialog.h \
    ImportMenu.h \
    FileMenu.h \
    LayerEditWidget.h \
    LayerSpeedControlWidget.h \
    BorderGraphicsPixmapItem.h \
    Settings.h \
    SettingsDialog.h \
    ColorPushButton.h

FORMS    +=

unix:!macx:!symbian: LIBS += -L$$PWD/../../../../../../usr/lib/ -lluabind
#unix:!macx:!symbian: LIBS += -L$$PWD/../../../../../../usr/lib/ -llua

RESOURCES += \
    icons.qrc

unix: CONFIG += link_pkgconfig
#unix: PKGCONFIG += lua5.2

unix|win32: LIBS += -llua5.2

unix: PKGCONFIG += lua5.2
