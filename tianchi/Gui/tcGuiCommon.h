/// ********************************************************************************************************************
/// @copyright Tianchi C++ source library for Qt5 (天池共享源码库)\n
/// 天池共享源码库开发组(www.qtcn.org)\n
/// @license 授权协议：请阅读天池共享源码库附带的授权协议(LICENSE.LGPLv2.1)\n
/// ********************************************************************************************************************
/// @file tcGuiCommon.h
/// @brief 与 Gui 相关的常用公共单元。
/// @version 1.0
/// @date 2014.12.17
/// @author 圣域天子(Jonix@qtcn.org)
///
/// ====================================================================================================================

#pragma once
#ifndef TIANCHI_TCGUICOMMON_H
#define TIANCHI_TCGUICOMMON_H

#ifndef TIANCHI_API
    #define TIANCHI_API
#endif

#include <QWidget>
#include <QApplication>
#include <QTextEdit>

extern "C"
{

} // End of extern "C";

/// @brief 把当前窗口移动到桌面正中间
#define MOVETO_DESKTOPCENTER() \
    move((qApp->desktop()->availableGeometry().bottomRight()-geometry().bottomRight()) /2);

/// @brief 限制 QTextEdit 输入文字的最大长度
void TIANCHI_API onTextChanged_limitMaxLength(QTextEdit* editor, int maxLength);

#endif // TIANCHI_TCGUICOMMON_H
