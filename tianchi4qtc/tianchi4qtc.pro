TC_COMPONENT = ../tianchi/Component

QT += widgets designer concurrent printsupport

TARGET = tianchi4qtc
DESTDIR = ../bin
TEMPLATE = lib
CONFIG += c++11

# Tianchi
INCLUDEPATH += tianchi $$TC_COMPONENT/tianchi

HEADERS += \
    tianchi/qcustomplotPlugin.h \
    tianchi/tcColorWheelPlugin.h \
    tianchi/tcDateEditPlugin.h \
    $$TC_COMPONENT/tianchi/qcustomplot.h \
    $$TC_COMPONENT/tianchi/tcColorWheel.h \
    $$TC_COMPONENT/tianchi/tcDateEdit.h

SOURCES += \
    tianchi/qcustomplotPlugin.cpp \
    tianchi/tcColorWheelPlugin.cpp \
    tianchi/tcDateEditPlugin.cpp \
    $$TC_COMPONENT/tianchi/qcustomplot.cpp \
    $$TC_COMPONENT/tianchi/tcColorWheel.cpp \
    $$TC_COMPONENT/tianchi/tcDateEdit.cpp

RESOURCES += \
    tianchi/tianchi.qrc


# QSint:
# http://www.oschina.net/p/qsint

INCLUDEPATH += QSint $$TC_COMPONENT/QSint

HEADERS += \
    QSint/actionboxplugin.h \
    QSint/actiongroupplugin.h \
    QSint/actionlabelplugin.h \
    QSint/actionpanelplugin.h \
    QSint/colorgridplugin.h \
    $$TC_COMPONENT/QSint/actionbox.h \
    $$TC_COMPONENT/QSint/actiongroup.h \
    $$TC_COMPONENT/QSint/actionlabel.h \
    $$TC_COMPONENT/QSint/actionpanel.h \
    $$TC_COMPONENT/QSint/actionpanelscheme.h \
    $$TC_COMPONENT/QSint/androidpanelscheme.h \
    $$TC_COMPONENT/QSint/colorgrid.h \
    $$TC_COMPONENT/QSint/macpanelscheme.h \
    $$TC_COMPONENT/QSint/taskgroup_p.h \
    $$TC_COMPONENT/QSint/taskheader_p.h \
    $$TC_COMPONENT/QSint/winvistapanelscheme.h \
    $$TC_COMPONENT/QSint/winxppanelscheme.h

SOURCES += \
    QSint/actionboxplugin.cpp \
    QSint/actiongroupplugin.cpp \
    QSint/actionlabelplugin.cpp \
    QSint/actionpanelplugin.cpp \
    QSint/colorgridplugin.cpp \
    $$TC_COMPONENT/QSint/actionbox.cpp \
    $$TC_COMPONENT/QSint/actiongroup.cpp \
    $$TC_COMPONENT/QSint/actionlabel.cpp \
    $$TC_COMPONENT/QSint/actionpanel.cpp \
    $$TC_COMPONENT/QSint/actionpanelscheme.cpp \
    $$TC_COMPONENT/QSint/androidpanelscheme.cpp \
    $$TC_COMPONENT/QSint/colorgrid.cpp \
    $$TC_COMPONENT/QSint/macpanelscheme.cpp \
    $$TC_COMPONENT/QSint/taskgroup_p.cpp \
    $$TC_COMPONENT/QSint/taskheader_p.cpp \
    $$TC_COMPONENT/QSint/winvistapanelscheme.cpp \
    $$TC_COMPONENT/QSint/winxppanelscheme.cpp

RESOURCES += \
    $$TC_COMPONENT/QSint/schemes.qrc \
    QSint/QSint.qrc


# wwWidgets: http://www.wysota.eu.org/wwwidgets

INCLUDEPATH += wwWidgets $$TC_COMPONENT/wwWidgets

HEADERS += \
    wwWidgets/qwwHueSatPickerIface.h \
    wwWidgets/qwwHueSatRadialPickerIface.h \
    $$TC_COMPONENT/wwWidgets/qwwHueSatPicker.h \
    $$TC_COMPONENT/wwWidgets/qwwHueSatRadialPicker.h

SOURCES += \
    wwWidgets/qwwHueSatPickerIface.cpp \
    wwWidgets/qwwHueSatRadialPickerIface.cpp \
    $$TC_COMPONENT/wwWidgets/qwwHueSatPicker.cpp \
    $$TC_COMPONENT/wwWidgets/qwwHueSatRadialPicker.cpp \
    $$TC_COMPONENT/wwWidgets/wwglobal_p.cpp

RESOURCES += wwWidgets/wwWidgets.qrc

# plugins
INCLUDEPATH += $$PWD

HEADERS += \
    tcDesignerComponent.h \
    TianchiPlugin.h

SOURCES += \
    tcDesignerComponent.cpp \
    TianchiPlugin.cpp

RC_FILE += tianchi4qtc.rc
