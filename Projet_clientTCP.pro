QT += core network
QT -= gui

TARGET = Projet_clientTCP
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    client.cpp

HEADERS += \
    client.h

