#include "qwwHueSatPickerIface.h"
#include "qwwHueSatPicker.h"
#include <QSettings>

QwwHueSatPickerIface::QwwHueSatPickerIface(QObject* parent)
    : TianchiPlugin(parent)
{
}

QIcon QwwHueSatPickerIface::icon() const
{
    return QIcon(QPixmap(":/images/hspicker.png"));
}

QWidget* QwwHueSatPickerIface::createWidget(QWidget* parent)
{
    return new QwwHueSatPicker(parent);
}
