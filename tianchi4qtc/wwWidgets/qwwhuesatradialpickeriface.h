#ifndef QWWHUESATRADIALPICKERIFACE_H
#define QWWHUESATRADIALPICKERIFACE_H

#include "TianchiPlugin.h"

class QwwHueSatRadialPickerIface : public TianchiPlugin
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface);
public:
    QwwHueSatRadialPickerIface(QObject* parent = 0);
    QIcon icon() const override;
    QWidget *createWidget(QWidget* parent);
};

#endif
