#-------------------------------------------------
#
# Project created by QtCreator 2018-08-24T18:54:21
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Tic-Tac-Toe
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
    ClientMainWindow.cpp \
    Game.cpp \
    AI.cpp \
    MainWindowManager.cpp \
    GameController.cpp \
    TcpClient.cpp \
    TcpServer.cpp \
    Utils.cpp \
    data/Message.cpp \
    data/Player.cpp \
    data/BoardModel.cpp \
    widgets/BoardWidget.cpp \
    widgets/GamePlayWidget.cpp \
    widgets/SelectDifficultyWidget.cpp \
    widgets/WelcomeWidget.cpp


HEADERS  += \
    ClientMainWindow.h \
    Game.h \
    AI.h \
    MainWindowManager.h \
    GameController.h \
    TcpClient.h \
    TcpServer.h \
    Utils.h \
    data/data.h \
    data/config.h \
    data/Message.h \
    data/Player.h \
    data/BoardModel.h \
    widgets/BoardWidget.h \
    widgets/GamePlayWidget.h \
    widgets/SelectDifficultyWidget.h \
    widgets/WelcomeWidget.h


FORMS    += \
    ClientMainWindow.ui \
    MainWindowManager.ui \
    ClientWindow.ui \
    widgets/BoardWidget.ui \
    widgets/GamePlayWidget.ui \
    widgets/SelectDifficultyWidget.ui \
    widgets/WelcomeWidget.ui

DISTFILES += \
    README.txt

RESOURCES += \
    images.qrc
