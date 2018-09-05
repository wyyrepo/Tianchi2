/// ********************************************************************************************************************
/// @copyright Tianchi C++ source library for Qt5 (天池共享源码库)\n
/// 天池共享源码库开发组(www.qtcn.org)\n
/// @license 授权协议：请阅读天池共享源码库附带的授权协议(LICENSE.LGPLv2.1)\n
/// ********************************************************************************************************************
/// @file tcdateedit.h
/// @brief 允许输入为空的日期选择插件(IDE控件)
/// @version 1.1
/// @date 2014.12.11
/// @author 圣域天子(Jonix@qtcn.org)
///
/// ====================================================================================================================

#pragma once
#ifndef TIANCHI_TCDATEEDIT_H
#define TIANCHI_TCDATEEDIT_H

#ifndef TIANCHI_API
    #define TIANCHI_API
#endif

#include <QDate>
#include <QByteArray>
#include <QComboBox>
#include <QCalendarWidget>
#include <QDebug>

/// @brief 允许输入为空的日期选择插件
class TIANCHI_API TcDateEdit : public QComboBox
{
    Q_OBJECT
    Q_PROPERTY(QDate date READ date WRITE setDate RESET unsetDate)
Q_SIGNALS:
    void dateChanged(const QDate& date);

protected slots:
    void setMinimumDate(const QDate& adate);
    void setMaximumDate(const QDate& adate);
    void calendarClicked(QDate);
    void textChanged(const QString& text);

private:
    QCalendarWidget* m_calendar;

    QString DateText(const QString& s);

protected:
    void focusInEvent(QFocusEvent *e);
    void mousePressEvent(QMouseEvent *e);

public:
    TcDateEdit(QWidget *parent = 0);
    virtual ~TcDateEdit();

    QDate date() const;
    void setDate(QDate value);
    void unsetDate();

    inline void setDate(QDateTime value) { setDate(value.date()); }

    inline bool isEmpty() const { return currentText().trimmed().isEmpty(); }

    qint64 toUtcMSecsSinceEpoch();     // 时间截(兼容Java)
    qint64 toUtcLastMSecsSinceEpoch(); // 23:59:59 的时间截
};

#endif // TIANCHI_TCDATEEDIT_H

