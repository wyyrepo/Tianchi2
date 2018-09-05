/// ********************************************************************************************************************
/// @copyright Tianchi C++ source library for Qt5 (天池共享源码库)\n
/// 天池共享源码库开发组(www.qtcn.org)\n
/// @license 授权协议：请阅读天池共享源码库附带的授权协议(LICENSE.LGPLv2.1)\n
/// ********************************************************************************************************************
/// @file tcShadowDialog.h
/// @brief 无边框窗口加阴影，缩放功能
/// @version 1.0
/// @date 2014.12.19
/// @author 圣域天子(Jonix@qtcn.org)
///
/// ====================================================================================================================

#pragma once
#ifndef TIANCHI_TCSHADOWDIALOG_H
#define TIANCHI_TCSHADOWDIALOG_H

#include <QDialog>
#include <QPixmap>
#include <QVBoxLayout>

#ifndef TIANCHI_API
    #define TIANCHI_API
#endif

namespace Ui {
class TcShadowDialog;
}

class TIANCHI_API TcShadowDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TcShadowDialog(QWidget* parent, int shadowWidth=4);
    ~TcShadowDialog();

    static void paintShadow(QWidget* widget, int shadowWidth=3);
    static bool resizeEvent(const QByteArray&, void* msg, long* result, const QRect& wndRect);
    static bool sorptionEvent(const QByteArray&, void* msg, long*, int shadowWidth=0);

protected:
    Ui::TcShadowDialog* ui;

    QVBoxLayout*  clientLayout();

    void    setWndCaptionVisible(bool value);
    void    initClient(QWidget* widget, const QString& captionStyle="");

    void    setIcon(const QPixmap& pixmap);
    void    setCaption(const QString& caption);

    int     m_shadowWidth;
    bool    m_frameResize;

    virtual bool    eventFilter(QObject* target, QEvent* event) override;
    virtual void    paintEvent(QPaintEvent*) override;
    virtual bool    nativeEvent(const QByteArray& eventType, void* msg, long* result) override;
};

#define TC_PAINTSHADOW(w) \
    virtual void paintEvent(QPaintEvent*) override \
    { TcShadowDialog::paintShadow(this, w); }

#define TC_WINDOWRESIZE(widget) \
    virtual bool    nativeEvent(const QByteArray& eventType, void* msg, long* result) override \
    { return TcShadowDialog::resizeEvent(eventType, msg, result, widget->geometry()); }


#endif // TIANCHI_TCSHADOWDIALOG_H
