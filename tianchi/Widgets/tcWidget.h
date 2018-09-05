/// ********************************************************************************************************************
/// @copyright Tianchi C++ source library for Qt5 (天池共享源码库)\n
/// 天池共享源码库开发组(www.qtcn.org)\n
/// @license 授权协议：请阅读天池共享源码库附带的授权协议(LICENSE.LGPLv2.1)\n
/// ********************************************************************************************************************
/// @file tcWidget.h
/// @brief QWidget 相关扩展
/// @version 1.1
/// @date 2014.12.24
/// @author 圣域天子(Jonix@qtcn.org)
///
/// ====================================================================================================================

#pragma once
#ifndef TIANCHI_TCWIDGET_H
#define TIANCHI_TCWIDGET_H

#ifndef TIANCHI_API
    #define TIANCHI_API
#endif

#include <QWidget>

class TIANCHI_API TcWidget
{
public:
    static void styleSheetPaintEvent(QWidget* widget, QPaintEvent*);

    inline QWidget* parentForm() const { return m_parentForm; }
    inline void     setParentForm(QWidget* value) { m_parentForm = value; }
private:
    QWidget*    m_parentForm;
};

#define TCDEFINE_WIDGET_STYLESHEET_PAINT() \
    void paintEvent(QPaintEvent* event) \
    { TcWidget::styleSheetPaintEvent(this, event); }

#endif // TIANCHI_TCWIDGET_H
