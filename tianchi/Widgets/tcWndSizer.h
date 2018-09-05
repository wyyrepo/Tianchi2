/// ********************************************************************************************************************
/// @copyright Tianchi C++ source library for Qt5 (天池共享源码库)\n
/// 天池共享源码库开发组(www.qtcn.org)\n
/// @license 授权协议：请阅读天池共享源码库附带的授权协议(LICENSE.LGPLv2.1)\n
/// ********************************************************************************************************************
/// @file tcWndSizer.h
/// @brief 缩放无框窗口
/// @version 1.1
/// @date 2013.04.10
/// @author 圣域天子(Jonix@qtcn.org)
///
/// ====================================================================================================================

#pragma once
#ifndef TIANCHI_TCWNDSIZER_H
#define TIANCHI_TCWNDSIZER_H

#ifndef TIANCHI_API
    #define TIANCHI_API
#endif

#include <QWidget>
#include <QCursor>

/// @code
///    // 在窗口的构造函数中使用
///    new TcWindowSizer(this);
/// @endcode
class TIANCHI_API TcWndSizer : public QObject
{
public:
    TcWndSizer(QWidget* parent);

    void setBorderWidth(int width);

private:
    int m_borderWidth;

    QWidget*    m_widget;
    QCursor     m_widgetCursor;

    bool eventFilter(QObject* target, QEvent* event);
};

#endif // TIANCHI_TCWNDSIZER_H
