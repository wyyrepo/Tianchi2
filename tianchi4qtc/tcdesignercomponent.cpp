#include "tcDesignerComponent.h"

#include "qcustomplotPlugin.h"
#include "tcColorWheelPlugin.h"
#include "tcDateEditPlugin.h"

#include "actionboxplugin.h"
#include "actionlabelplugin.h"
#include "actiongroupplugin.h"
#include "actionpanelplugin.h"
#include "colorgridplugin.h"

#include "qwwHueSatPickerIface.h"
#include "qwwHueSatRadialPickerIface.h"

#include <QtPlugin>

TcDesignerWidgets::TcDesignerWidgets(QObject *parent)
    : QObject(parent)
{
    m_plugins.append(new QCustomPlotPlugin(this));
    m_plugins.append(new TcDateEditPlugin(this));
    m_plugins.append(new TcColorWheelPlugin(this));

    m_plugins.append(new ActionBoxPlugin(this));
    m_plugins.append(new ActionLabelPlugin(this));
    m_plugins.append(new ActionGroupPlugin(this));
    m_plugins.append(new ActionPanelPlugin(this));
    m_plugins.append(new ColorGridPlugin(this));

    m_plugins.append(new QwwHueSatPickerIface(this));
    m_plugins.append(new QwwHueSatRadialPickerIface(this));
}

QList<QDesignerCustomWidgetInterface*> TcDesignerWidgets::customWidgets() const
{
    return m_plugins;
}

#if (QT_VERSION < QT_VERSION_CHECK(5, 0, 0))
Q_EXPORT_PLUGIN(TcDesignerWidgets)
#endif
