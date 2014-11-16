TEMPLATE = app

TARGET  = test

include($$PWD/test_app.pri)

INCLUDEPATH += $$PWD/../

CONFIG += console

QT += core
QT -= gui

DESTDIR = ../

LIBS += -L../
LIBS += -lQMultiFile
