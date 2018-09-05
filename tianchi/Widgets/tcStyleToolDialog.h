/// ********************************************************************************************************************
/// @copyright Tianchi C++ source library for Qt5 (天池共享源码库)\n
/// 天池共享源码库开发组(www.qtcn.org)\n
/// @license 授权协议：请阅读天池共享源码库附带的授权协议(LICENSE.LGPLv2.1)\n
/// ********************************************************************************************************************
/// @file tcStyleToolDialog.h
/// @brief 无边框窗口加阴影，缩放功能
/// @version 1.0
/// @date 2014.12.19
/// @author 圣域天子(Jonix@qtcn.org)
///
/// ====================================================================================================================

#pragma once
#ifndef TIANCHI_TCSTYLETOOLDIALOG_H
#define TIANCHI_TCSTYLETOOLDIALOG_H

#include <QDialog>
#include <QPixmap>
#include <QVBoxLayout>

#ifndef TIANCHI_API
    #define TIANCHI_API
#endif

namespace Ui {
class TcStyleToolDialog;
}

class TIANCHI_API TcStyleToolDialog : public QDialog
{
    typedef QDialog inherited;
    Q_OBJECT
public:
    static void paintShadow(QWidget* widget, int shadowWidth=3);
    static bool resizeEvent(const QByteArray&, void* msg, long* result, const QRect& wndRect);
    static bool sorptionEvent(const QByteArray&, void* msg, long*, int shadowWidth=0);

    explicit TcStyleToolDialog(QWidget* parent=0);
    ~TcStyleToolDialog();

protected:
    Ui::TcStyleToolDialog* ui;

    inline void setDialogResize(bool value) { m_dialogResize = value; }
    void        setShadowWidth(int shadowWidth);
    QLayout*    clientLayout();
    void        initClient(QWidget* widget);

    virtual bool    isMoveBar(QWidget* moveBar) const { Q_UNUSED(moveBar); return false; }

    virtual void    paintEvent(QPaintEvent*) override;
    virtual bool    nativeEvent(const QByteArray& eventType, void* msg, long* result) override;

private:
    bool    m_dialogResize;
    int     m_shadowWidth;
};

#define TC_PAINTSHADOW(w) \
    virtual void paintEvent(QPaintEvent*) override \
    { TcStyleToolDialog::paintShadow(this, w); }

#define TC_WINDOWRESIZE(widget) \
    virtual bool    nativeEvent(const QByteArray& eventType, void* msg, long* result) override \
    { return TcStyleToolDialog::resizeEvent(eventType, msg, result, widget->geometry()); }


#endif // TIANCHI_TCSTYLETOOLDIALOG_H
