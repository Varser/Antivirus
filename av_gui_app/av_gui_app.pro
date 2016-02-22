#-------------------------------------------------
#
# Project created by QtCreator 2016-02-03T21:40:52
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = av_gui_app
TEMPLATE = app
TEMPLATE  += subdirs
CONFIG   += ordered
SUBDIRS += av_gui_lib


SOURCES += main.cpp\
        widget.cpp \
    Buttons/pause_continue_button.cpp \
    Buttons/scan_stop_button.cpp \
    Buttons/progress_bar.cpp \
    Buttons/scan_results_text_edit.cpp \
    scanner_manager.cpp \
    scanner.cpp \
    file_scan.cpp

HEADERS  += widget.h \
    Buttons/pause_continue_button.h \
    Buttons/scan_stop_button.h \
    Buttons/progress_bar.h \
    Buttons/scan_results_text_edit.h \
    scanner_manager.h \
    scanner.h \
    file_scan.h

RESOURCES += \
    resources.qrc
