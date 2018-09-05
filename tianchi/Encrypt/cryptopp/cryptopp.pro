DESTDIR = ..\bin
TARGET = crypto++
TEMPLATE = lib
CONFIG += shared
CONFIG -= app_bundle
CONFIG -= qt

Debug: TARGET = $${TARGET}d

include(cryptopp.pri)

LIBS += -lws2_32
