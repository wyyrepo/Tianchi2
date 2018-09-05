#include "qcustomplotplugin.h"
#include "qcustomplot.h"
#include <QtPlugin>

QCustomPlotPlugin::QCustomPlotPlugin(QObject *parent)
    : QObject(parent), m_initialized(false)
{
}

QString QCustomPlotPlugin::name() const
{
    return "QCustomPlot";
}

QString QCustomPlotPlugin::includeFile() const
{
    return "qcustomplot.h";
}

QString QCustomPlotPlugin::group() const
{
    return tr("Tianchi Widgets");
}

QIcon QCustomPlotPlugin::icon() const
{
    return QIcon(":/images/qcustomplot.png");
}

QString QCustomPlotPlugin::toolTip() const
{
    return tr("QCustomPlot");
}

QString QCustomPlotPlugin::whatsThis() const
{
    return tr("QCustomPlot");
}

bool QCustomPlotPlugin::isContainer() const
{
    return false;
}

QWidget* QCustomPlotPlugin::createWidget(QWidget *parent)
{
    return new QCustomPlot(parent);
}

bool QCustomPlotPlugin::isInitialized() const
{
    return m_initialized;
}

void QCustomPlotPlugin::initialize(QDesignerFormEditorInterface * /*core*/)
{
    if (m_initialized)
        return;

    m_initialized = true;
}

QString QCustomPlotPlugin::domXml() const
{
    return QString("\
    <ui language=\"c++\">\
        <widget class=\"QCustomPlot\" name=\"customPlot\">\
        </widget>\
    </ui>");
}
