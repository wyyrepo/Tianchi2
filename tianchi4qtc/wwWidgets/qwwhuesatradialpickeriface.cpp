#include "qwwHueSatRadialPickerIface.h"
#include "qwwHueSatRadialPicker.h"

QwwHueSatRadialPickerIface::QwwHueSatRadialPickerIface(QObject *parent)
: TianchiPlugin(parent)
{
}

QIcon QwwHueSatRadialPickerIface::icon() const
{
    return QIcon(QPixmap(":/images/hsrpicker.png"));
}

QWidget * QwwHueSatRadialPickerIface::createWidget(QWidget* parent)
{
    return new QwwHueSatRadialPicker(parent);
}
