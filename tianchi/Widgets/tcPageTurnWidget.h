/// ********************************************************************************************************************
/// @copyright Tianchi C++ source library for Qt5 (天池共享源码库)\n
/// 天池共享源码库开发组(www.qtcn.org)\n
/// @license 授权协议：请阅读天池共享源码库附带的授权协议(LICENSE.LGPLv2.1)\n
/// ********************************************************************************************************************
/// @file tcPageTurnWidget.h
/// @brief 生成翻页按钮
/// @version 1.0
/// @date 2014.12.18
/// @author 圣域天子(Jonix@qtcn.org)
///
/// ====================================================================================================================

#pragma once
#ifndef TIANCHI_TCPAGETURNWIDGET_H
#define TIANCHI_TCPAGETURNWIDGET_H

#ifndef TIANCHI_API
    #define TIANCHI_API
#endif

#include <QWidget>
#include <QToolButton>

class TIANCHI_API TcPageTurnWidget : public QObject
{
    Q_OBJECT
public:
    explicit TcPageTurnWidget(QWidget* parent=0);
    ~TcPageTurnWidget();

    void newButtons(int pageNo, int records, int totalPages);
    void newButtons(int pageNo, int records, int totalPages, QObject* receiver, const char* member);
    void setAutoHide(QWidget* pageTurnBar);
    QString buttonStyle(const QString& style);
    void setButtonStyle(const QString& style);

Q_SIGNALS:
    void pageTurnClicked(int pageNo);

private slots:
    void evPageTurn_clicked();

private:
    QWidget*        m_pageTurnBar;
    QString         m_buttonStyle;
    QList<QWidget*> m_buttons;

    QToolButton*    newButton(const QString& caption, int pageNo, const QObject* receiver, const char* member);
};

#endif // TIANCHI_TCPAGETURNWIDGET_H
