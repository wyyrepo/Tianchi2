/// ********************************************************************************************************************
/// @copyright Tianchi C++ source library for Qt5 (天池共享源码库)\n
/// 天池共享源码库开发组(www.qtcn.org)\n
/// @license 授权协议：请阅读天池共享源码库附带的授权协议(LICENSE.LGPLv2.1)\n
/// ********************************************************************************************************************
/// @file tcAdminAuthorization.h
/// @brief 操作系统管理员权限的判断和提升权限执行程序
/// @version 1.0
/// @date 2014.12.11
/// @author 渡世白玉(dushibaiyu@yahoo.com)
/// @note 源码摘自 Qt5.3.2 / Qt-Install-Framework
///
/// ====================================================================================================================

#pragma once
#ifndef TIANCHI_TCADMINAUTHORIZATION_H
#define TIANCHI_TCADMINAUTHORIZATION_H

#ifndef TIANCHI_API
    #define TIANCHI_API
#endif

#include <QWidget>

/// @brief 操作系统管理员权限的判断和提升权限执行程序
class TIANCHI_API TcAdminAuthorization
{
public:
    /// @brief 判断当前运行的程序有没有管理员权限
    /// @return true: 有管理员权限, false: 没有管理员权限
    static bool hasAdminRights();

    /// @brief 以管理员身份启动新的程序
    /// @param parent       提示对话框的父级窗体。Win下没用。
    /// @param programs     要启动的程序的命令
    /// @param arguments    程序启动参数
    static bool execute(QWidget* parent, const QString& programs, const QStringList& arguments);

private:
    TcAdminAuthorization() {}
};

#endif // TIANCHI_TCADMINAUTHORIZATION_H
