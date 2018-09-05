/// ********************************************************************************************************************
/// @copyright Tianchi C++ source library for Qt5 (天池共享源码库)\n
/// 天池共享源码库开发组(www.qtcn.org)\n
/// @license 授权协议：请阅读天池共享源码库附带的授权协议(LICENSE.LGPLv2.1)\n
/// ********************************************************************************************************************
/// @file tcRunOnceChecker.h
/// @brief 程序单实例判断，检查是否当前程序是第一次启动
/// @version 1.0
/// @date 2014.12.12
/// @author 渡世白玉(dushibaiyu@yahoo.com)
/// @note 源码摘自 Qt5.3.2 / Qt-Install-Framework
///
/// ====================================================================================================================

#pragma once
#ifndef TIANCHI_TCRUNONCECHECKER_H
#define TIANCHI_TCRUNONCECHECKER_H

#ifndef TIANCHI_API
    #define TIANCHI_API
#endif

#include <QString>

/// @brief 检查是否当前程序是第一次启动
class TIANCHI_API TcRunOnceChecker
{
public:
    /// @brief 检查模式
    enum Dependencies
    {
        ProcessList, ///> 检查运行程序列表是否有其他实例
        Lockfile,    ///> 检查文件是否被锁定
        Both         ///> 两者全部检查
    };

    /// @brief 构造函数
    /// @param filename 要检查的是否锁定的文件
    explicit TcRunOnceChecker(const QString& filename = QString());
    ~TcRunOnceChecker();

    /// @brief 检查函数，根据检查选项，返回检查结果。
    /// @param depends 检查选项
    bool isRunning(Dependencies depends);

private:
    Q_DISABLE_COPY(TcRunOnceChecker)
    class Private;
    Private *d;
};

#endif // TIANCHI_TCRUNONCECHECKER_H
