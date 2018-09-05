#include "TianchiPlugin.h"

TianchiPlugin::TianchiPlugin(QObject* parent)
    : QObject(parent)
{
    m_initialized = false;
}

QString TianchiPlugin::name() const
{
    QString classname = metaObject()->className();
    classname.chop(5);
    return classname;
}

QString TianchiPlugin::includeFile() const
{
    return name().toLower().left(1) + name().right(name().length()-1)+".h";
}

QString TianchiPlugin::group() const
{
    return tr("Tianchi Widgets");
}

QIcon TianchiPlugin::icon() const
{
    return QIcon(":/images/"+name());
}

QString TianchiPlugin::toolTip() const
{
    return m_toolTip;
}

QString TianchiPlugin::whatsThis() const
{
    return m_whatsThis;
}

bool TianchiPlugin::isContainer() const
{
    return false;
}

bool TianchiPlugin::isInitialized() const
{
    return m_initialized;
}

void TianchiPlugin::initialize(QDesignerFormEditorInterface*)
{
    m_initialized = true;
}

QString TianchiPlugin::domXml() const
{
    return QString("<ui language=\"c++\"><widget class=\""+name()+"\" name=\""+name().toLower()+"\"></widget></ui>");
}

