QT += core
QT -= gui
QT += network

CONFIG += c++11

TARGET = av_core_app
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    connection.cpp \
    ipc.cpp \
    scanner_manager.cpp \
    scanner.cpp \
    database.cpp

HEADERS += \
    connection.h \
    ipc.h \
    scanner_manager.h \
    scanner.h \
    database.h
