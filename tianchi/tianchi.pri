QT += core
CONFIG += c++11

# =====================================================================================================================
# Common
# ---------------------------------------------------------------------------------------------------------------------
INCLUDEPATH += $$PWD/Common

HEADERS += \
    $$PWD/Common/tcCommon.h \
    $$PWD/Common/tcInvoke.h

SOURCES += \
    $$PWD/Common/tcCommon.cpp \
    $$PWD/Common/tcInvoke.cpp


# =====================================================================================================================
# Component
# ---------------------------------------------------------------------------------------------------------------------
QT += printsupport
INCDIR = $$PWD/Component
INCLUDEPATH += $$INCDIR

# tianchi
INCLUDEPATH += $$INCDIR/tianchi
HEADERS += \
    $$INCDIR/tianchi/qcustomplot.h \
    $$INCDIR/tianchi/tcDateEdit.h \
    $$INCDIR/tianchi/tcColorWheel.h

SOURCES += \
    $$INCDIR/tianchi/qcustomplot.cpp \
    $$INCDIR/tianchi/tcDateEdit.cpp \
    $$INCDIR/tianchi/tcColorWheel.cpp


# QSint: http://www.oschina.net/p/qsint

INCLUDEPATH += $$INCDIR/QSint

HEADERS += \
    $$INCDIR/QSint/actionbox.h \
    $$INCDIR/QSint/actiongroup.h \
    $$INCDIR/QSint/actionlabel.h \
    $$INCDIR/QSint/actionpanel.h \
    $$INCDIR/QSint/actionpanelscheme.h \
    $$INCDIR/QSint/androidpanelscheme.h \
    $$INCDIR/QSint/colorgrid.h \
    $$INCDIR/QSint/macpanelscheme.h \
    $$INCDIR/QSint/taskgroup_p.h \
    $$INCDIR/QSint/taskheader_p.h \
    $$INCDIR/QSint/winvistapanelscheme.h \
    $$INCDIR/QSint/winxppanelscheme.h

SOURCES += \
    $$INCDIR/QSint/actionbox.cpp \
    $$INCDIR/QSint/actiongroup.cpp \
    $$INCDIR/QSint/actionlabel.cpp \
    $$INCDIR/QSint/actionpanel.cpp \
    $$INCDIR/QSint/actionpanelscheme.cpp \
    $$INCDIR/QSint/androidpanelscheme.cpp \
    $$INCDIR/QSint/colorgrid.cpp \
    $$INCDIR/QSint/macpanelscheme.cpp \
    $$INCDIR/QSint/taskgroup_p.cpp \
    $$INCDIR/QSint/taskheader_p.cpp \
    $$INCDIR/QSint/winvistapanelscheme.cpp \
    $$INCDIR/QSint/winxppanelscheme.cpp

RESOURCES += \
    $$INCDIR/QSint/schemes.qrc


# wwWidgets: http://www.wysota.eu.org/wwWidgets

INCLUDEPATH += $$INCDIR/wwWidgets

HEADERS += \
    $$INCDIR/wwWidgets/wwglobal.h \
    $$INCDIR/wwWidgets/qwwHueSatPicker.h \
    $$INCDIR/wwWidgets/qwwHueSatRadialPicker.h \

SOURCES += \
    $$INCDIR/wwWidgets/wwglobal_p.cpp \
    $$INCDIR/wwWidgets/qwwHueSatPicker.cpp \
    $$INCDIR/wwWidgets/qwwHueSatRadialPicker.cpp


# =====================================================================================================================
# Encrypt
# ---------------------------------------------------------------------------------------------------------------------
INCLUDEPATH += $$PWD/Encrypt

HEADERS += \
    $$PWD/Encrypt/tcAES.h \
    $$PWD/Encrypt/tcRSA.h

SOURCES += \
    $$PWD/Encrypt/tcAES.cpp \
    $$PWD/Encrypt/tcRSA.cpp

# 第三方源码包 - Crypto++
CRYPTOPP_DIR = $$PWD/Encrypt/cryptopp
include($$CRYPTOPP_DIR/cryptopp.pri)


# =====================================================================================================================
# Gui
# ---------------------------------------------------------------------------------------------------------------------
QT += gui

INCLUDEPATH += $$PWD/Gui

HEADERS += \
    $$PWD/Gui/tcAutoCursor.h \
    $$PWD/Gui/tcGuiCommon.h \
    $$PWD/Gui/tcImageAdjust.h

SOURCES += \
    $$PWD/Gui/tcAutoCursor.cpp \
    $$PWD/Gui/tcGuiCommon.cpp \
    $$PWD/Gui/tcImageAdjust.cpp


# =====================================================================================================================
# IO
# ---------------------------------------------------------------------------------------------------------------------
INCLUDEPATH += $$PWD/IO

HEADERS += \
    $$PWD/IO/tcExcelReader.h \
    $$PWD/IO/tcIO.h \
    $$PWD/IO/tcLog.h

SOURCES += \
    $$PWD/IO/tcExcelReader.cpp \
    $$PWD/IO/tcIO.cpp \
    $$PWD/IO/tcLog.cpp

win32:{

    QT += axcontainer

    HEADERS += \
        $$PWD/IO/tcExcel.h

    SOURCES += \
        $$PWD/IO/tcExcel.cpp

}


# =====================================================================================================================
# Multimedia
# ---------------------------------------------------------------------------------------------------------------------
INCLUDEPATH += $$PWD/Multimedia

HEADERS += \
    $$PWD/Multimedia/tcTextToSpeech.h

SOURCES += \
    $$PWD/Multimedia/tcTextToSpeech.cpp


# =====================================================================================================================
# Network
# ---------------------------------------------------------------------------------------------------------------------
QT += network

INCLUDEPATH += $$PWD/Network

HEADERS += \
    $$PWD/Network/tcDownloader.h \
    $$PWD/Network/tcFtp.h \
    $$PWD/Network/tcHttp.h \
    $$PWD/Network/tcUdp.h

SOURCES += \
    $$PWD/Network/tcDownloader.cpp \
    $$PWD/Network/tcFtp.cpp \
    $$PWD/Network/tcHttp.cpp \
    $$PWD/Network/tcUdp.cpp


# =====================================================================================================================
# OS
# ---------------------------------------------------------------------------------------------------------------------
INCLUDEPATH += $$PWD/OS

HEADERS += \
    $$PWD/OS/tcAdminAuthorization.h \
    $$PWD/OS/tcChinese.h \
    $$PWD/OS/tcOS.h \
    $$PWD/OS/tcRunOnceChecker.h \
    $$PWD/OS/tcSelfRestarter.h \
    $$PWD/OS/tcSystemInfo.h \
    $$PWD/OS/tcWindows.h

SOURCES += \
    $$PWD/OS/tcChinese.cpp \
    $$PWD/OS/tcOS.cpp \
    $$PWD/OS/tcRunOnceChecker.cpp \
    $$PWD/OS/tcSelfRestarter.cpp \
    $$PWD/OS/tcSystemInfo.cpp \
    $$PWD/OS/tcWindows.cpp

win32:{

    QT += axcontainer

    SOURCES += \
        $$PWD/OS/tcAdminAuthorization_win.cpp \
        $$PWD/OS/tcSystemInfo_win.cpp

    LIBS += -lversion

    win32-g++*:
    {
        LIBS += -lmpr -lmprapi
    }

    win32-msvc*:
    {
        LIBS += -lshell32
    }
}
unix:{
    macx:{
        SOURCES += \
            $$PWD/OS/tcAdminAuthorization_mac.cpp \
            $$PWD/OS/tcSystemInfo_mac.cpp

        LIBS += -framework Carbon -framework Security

    }else{
        SOURCES += \
            $$PWD/OS/tcAdminAuthorization_x11.cpp \
            $$PWD/OS/tcSystemInfo_x11.cpp

        LIBS += -lutil
    }
}


# =====================================================================================================================
# QRCode
# ---------------------------------------------------------------------------------------------------------------------
INCLUDEPATH += $$PWD/QRCode

# 二维码解码包
HEADERS += $$PWD/QRCode/tcQrencode.h
SOURCES += $$PWD/QRCode/tcQrencode.cpp
# 第三方源码包 - QRencode
QRENCODE_DIR = $$PWD/QRCode/qrencode
include($$QRENCODE_DIR/qrencode.pri)

# 二维码解码包
HEADERS += $$PWD/QRCode/tcZxing.h
SOURCES += $$PWD/QRCode/tcZxing.cpp
# 第三方源码包 - ZXing
ZXING_DIR = $$PWD/QRCode/zxing
include($$ZXING_DIR/zxing.pri)

# =====================================================================================================================
# Widgets
# ---------------------------------------------------------------------------------------------------------------------
QT += gui

INCLUDEPATH += $$PWD/Widgets

HEADERS += \
    $$PWD/Widgets/tcPageTurnWidget.h \
    $$PWD/Widgets/tcScreenshot.h \
    $$PWD/Widgets/tcShadowDialog.h \
    $$PWD/Widgets/tcViewHeaderSetupDialog.h \
    $$PWD/Widgets/tcWidget.h

SOURCES += \
    $$PWD/Widgets/tcPageTurnWidget.cpp \
    $$PWD/Widgets/tcScreenshot.cpp \
    $$PWD/Widgets/tcShadowDialog.cpp \
    $$PWD/Widgets/tcViewHeaderSetupDialog.cpp \
    $$PWD/Widgets/tcWidget.cpp

FORMS += \
    $$PWD/Widgets/tcScreenshot.ui \
    $$PWD/Widgets/tcShadowDialog.ui \
    $$PWD/Widgets/tcViewHeaderSetupDialog.ui

RESOURCES += \
    $$PWD/Widgets/tcShadowDialog.qrc \
    $$PWD/Widgets/tcViewHeaderSetupDialog.qrc


