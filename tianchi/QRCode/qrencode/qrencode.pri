isEmpty($$QRENCODE_DIR)
{
    $$QRENCODE_DIR = $$PWD
}

INCLUDEPATH += $$QRENCODE_DIR

HEADERS += \
    $$QRENCODE_DIR/qrencode.h \
    $$QRENCODE_DIR/qrspec.h \
    $$QRENCODE_DIR/mqrspec.h \
    $$QRENCODE_DIR/bitstream.h \
    $$QRENCODE_DIR/qrinput.h \
    $$QRENCODE_DIR/rscode.h \
    $$QRENCODE_DIR/split.h \
    $$QRENCODE_DIR/mask.h \
    $$QRENCODE_DIR/mmask.h

SOURCES += \
    $$QRENCODE_DIR/qrencode.c \
    $$QRENCODE_DIR/qrspec.c \
    $$QRENCODE_DIR/mqrspec.c \
    $$QRENCODE_DIR/bitstream.c \
    $$QRENCODE_DIR/qrinput.c \
    $$QRENCODE_DIR/rscode.c \
    $$QRENCODE_DIR/split.c \
    $$QRENCODE_DIR/mask.c \
    $$QRENCODE_DIR/mmask.c

win32:{

}
unix:{
    macx:{

    }else{

    }
}
