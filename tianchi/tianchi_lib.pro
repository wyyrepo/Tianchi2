QT += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++11 
CONFIG += staticlib
DESTDIR = ../bin
TARGET = $$qtLibraryTarget(tianchi_lib)
TEMPLATE = lib

#DEFINES += TIANCHI_API=Q_CORE_EXPORT

include($$PWD/tianchi_all.pri)

VERSION = 0.2.0

