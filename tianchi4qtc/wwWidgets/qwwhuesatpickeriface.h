#ifndef QWWHUESATPICKERIFACE_H
#define QWWHUESATPICKERIFACE_H

#include "TianchiPlugin.h"

class QwwHueSatPickerIface : public TianchiPlugin
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface);
public:
    QwwHueSatPickerIface(QObject* parent=0);
    QIcon icon() const override;
    QWidget *createWidget(QWidget* parent);
};

#endif
