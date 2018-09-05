/// ********************************************************************************************************************
/// @copyright Tianchi C++ source library for Qt5 (天池共享源码库)\n
/// 天池共享源码库开发组(www.qtcn.org)\n
/// @license 授权协议：请阅读天池共享源码库附带的授权协议(LICENSE.LGPLv2.1)\n
/// ********************************************************************************************************************
/// @file tcScreenshot.h
/// @brief 对桌面指定区域进行截屏
/// @version 1.0
/// @date 2014.12.22
/// @author 圣域天子(Jonix@qtcn.org)
///
/// ====================================================================================================================

#pragma once
#ifndef TIANCHI_TCSCREENSHOT_H
#define TIANCHI_TCSCREENSHOT_H

#include <QWidget>
#include <QCursor>

namespace Ui {
class TcScreenshot;
}

class TcScreenshot : public QWidget
{
    Q_OBJECT
public:
    explicit TcScreenshot();
    ~TcScreenshot();

    void initSightRect(const QRect& rt);

//    QPixmap photograph();

    inline QPixmap pixmap() const { return m_pixmap; }

Q_SIGNALS:
    void sightRect(const QRect& rt);
    void photograph(const QPixmap& pixmap);

private:
    Ui::TcScreenshot* ui;

    QRect m_hole_rt;
    QRect m_mask_rt1;
    QRect m_mask_rt2;
    QRect m_mask_rt3;
    QRect m_mask_rt4;

    // 5  1   9
    // 4      8
    // 6  2  10
    QRect m_grip_1;  // 上
    QRect m_grip_2;  // 下
    QRect m_grip_4;  // 左
    QRect m_grip_8;  // 右
    QRect m_grip_5;  // 左上
    QRect m_grip_6;  // 左下
    QRect m_grip_9;  // 右上
    QRect m_grip_10; // 右下

    QCursor m_defaultCursor;
    int     m_moveHole;
    QPoint  m_pressedPos;

    QPixmap m_pixmap;

    void makeRects();

    virtual void paintEvent(QPaintEvent*) override;
    virtual void mousePressEvent(QMouseEvent*) override;
    virtual void mouseReleaseEvent(QMouseEvent*) override;
    virtual void mouseDoubleClickEvent(QMouseEvent*) override;
    virtual void mouseMoveEvent(QMouseEvent*) override;
};

#endif // TIANCHI_TCSCREENSHOT_H
