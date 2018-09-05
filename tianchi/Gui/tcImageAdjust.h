/// ********************************************************************************************************************
/// @copyright Tianchi C++ source library for Qt5 (天池共享源码库)\n
/// 天池共享源码库开发组(www.qtcn.org)\n
/// @license 授权协议：请阅读天池共享源码库附带的授权协议(LICENSE.LGPLv2.1)\n
/// ********************************************************************************************************************
/// @file tcImageAdjust.h
/// @brief 图片简单处理(柔化, 锐化, 灰度化, 黑白化, 底片化, 浮雕化)
/// @version 1.0
/// @date 2015.01.21
/// @author foxgod / www.qtcn.org
///
/// ====================================================================================================================

#pragma once
#ifndef TIANCHI_TCIMAGEADJUST_H
#define TIANCHI_TCIMAGEADJUST_H

#include <QImage>

/// @brief 图片简单处理(柔化, 锐化, 灰度化, 黑白化, 底片化, 浮雕化)
class TcImageAdjust
{
public:
    /// @brief 图片柔化
    static bool soften(QImage& image);
    /// @brief 图片锐化
    static bool sharpen(QImage& image);
    /// @brief 图片灰度化
    static bool grayscale(QImage& image);
    /// @brief 图片黑白化
    static bool blackwhite(QImage& image);
    /// @brief 图片底片化
    static bool negative(QImage& image);
    /// @brief 图片浮雕化
    static bool relief(QImage& image);
};

#endif // TIANCHI_TCIMAGEADJUST_H
