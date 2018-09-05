#include "tcColorWheelPlugin.h"
#include "tcColorWheel.h"
#include <QtPlugin>

TcColorWheelPlugin::TcColorWheelPlugin(QObject *parent)
    : QObject(parent), m_initialized(false)
{
}

QString TcColorWheelPlugin::name() const
{
    return "TcColorWheel";
}

QString TcColorWheelPlugin::includeFile() const
{
    return "tcColorWheel.h";
}

QString TcColorWheelPlugin::group() const
{
    return tr("Tianchi Widgets");
}

QIcon TcColorWheelPlugin::icon() const
{
    return QIcon(":/images/TcColorWheel.png");
}

QString TcColorWheelPlugin::toolTip() const
{
    return tr("Color ring.");
}

QString TcColorWheelPlugin::whatsThis() const
{
    return tr("Color ring.");
}

bool TcColorWheelPlugin::isContainer() const
{
    return false;
}

QWidget* TcColorWheelPlugin::createWidget(QWidget *parent)
{
    return new TcColorWheel(parent);
}

bool TcColorWheelPlugin::isInitialized() const
{
    return m_initialized;
}

void TcColorWheelPlugin::initialize(QDesignerFormEditorInterface * /*core*/)
{
    if (m_initialized)
        return;

    m_initialized = true;
}

QString TcColorWheelPlugin::domXml() const
{
    return QString("\
    <ui language=\"c++\">\
        <widget class=\"TcColorWheel\" name=\"tcColorWheel\">\
        </widget>\
    </ui>");
}
