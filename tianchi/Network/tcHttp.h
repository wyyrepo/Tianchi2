/// ********************************************************************************************************************
/// @copyright Tianchi C++ source library for Qt5 (天池共享源码库)\n
/// 天池共享源码库开发组(www.qtcn.org)\n
/// @license 授权协议：请阅读天池共享源码库附带的授权协议(LICENSE.LGPLv2.1)\n
/// ********************************************************************************************************************
/// @file tcHttp.h
/// @brief http/https 请求由异步转为同步，即堵塞等待。常用于登录时等待返回
/// @version 1.0
/// @date 2014.12.12
/// @author 圣域天子(Jonix@qtcn.org)
///
/// ====================================================================================================================

#pragma once
#ifndef TIANCHI_TCHTTP_H
#define TIANCHI_TCHTTP_H

#ifndef TIANCHI_API
    #define TIANCHI_API
#endif

#include <QByteArray>


class TIANCHI_API TcHttp
{
public:
    TcHttp(int timeout=30000);

    /// @brief 使用 get 方式进行请求
    /// @param url 地址以及参数，支持 http/https
    QByteArray get(const QString& url);
    /// @brief 使用 post 方式进行请求
    /// @param url 地址
    /// @param content 参数表
    QByteArray post(const QString& url, const QByteArray& content);

    inline int timeout() const { return m_timeout; }
    inline void setTimeout(int value) { m_timeout = value; }

protected:
    int m_timeout;
};

#endif // TIANCHI_TCHTTP_H

