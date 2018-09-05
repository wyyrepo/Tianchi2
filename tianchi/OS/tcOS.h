/// ********************************************************************************************************************
/// @copyright Tianchi C++ source library for Qt5 (天池共享源码库)\n
/// 天池共享源码库开发组(www.qtcn.org)\n
/// @license 授权协议：请阅读天池共享源码库附带的授权协议(LICENSE.LGPLv2.1)\n
/// ********************************************************************************************************************
/// @file tcOS.h
/// @brief 操作系统相关功能
/// @version 1.1
/// @date 2013.04.10
/// @author 圣域天子(Jonix@qtcn.org)
///
/// ====================================================================================================================

#pragma once
#ifndef TIANCHI_TCOS_H
#define TIANCHI_TCOS_H

#ifndef TIANCHI_API
    #define TIANCHI_API
#endif

#include <QString>

/// @brief 与操作系统相关的操作类
class TIANCHI_API TcOS
{
public:
    /// @brief 取操作系统名称，支持Windows和Linux
    /// @note Windows从注册表中获取,Linux从依次从/etc下的os-release 
    ///       lsb-release, *-release文件获取
    static QString name();

    /// @brief 取操作系统的语言，仅支持 Windows
    /// @note 仅支持 Windows
    static QString language();

    /// @brief Windows 域用户登录，仅支持 Windows
    /// @param [in] Domain Windows 域名或本机机器名
    /// @param [in] UserID 域用户名或本机用户名
    /// @param [in] Password 用户密码
    /// @return true 登录成功
    /// @return false 登录失败
    /// @note 仅支持 Windows
    static bool userLogin(const QString& Domain, const QString& UserID, const QString& Password);
};

#endif // TIANCHI_TCOS_H
