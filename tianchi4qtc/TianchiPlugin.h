
#pragma once
#ifndef TIANCHI_WWINTERFACES_H
#define TIANCHI_WWINTERFACES_H

#include <QDesignerCustomWidgetInterface>

class TianchiPlugin : public QObject, public QDesignerCustomWidgetInterface
{
public:
    TianchiPlugin(QObject* parent=0);
    QString name() const;
    QString includeFile() const;
    QString group() const;
    QIcon icon() const;
    QString toolTip() const;
    QString whatsThis() const;
    bool isContainer() const;
    bool isInitialized() const;
    void initialize(QDesignerFormEditorInterface *core);
    QString domXml() const;
private:
    bool m_initialized;
    QString m_toolTip;
    QString m_whatsThis;
};


#endif
