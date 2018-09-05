/// ********************************************************************************************************************
/// @copyright Tianchi C++ source library for Qt5 (天池共享源码库)\n
/// 天池共享源码库开发组(www.qtcn.org)\n
/// @license 授权协议：请阅读天池共享源码库附带的授权协议(LICENSE.LGPLv2.1)\n
/// ********************************************************************************************************************
/// @file tcAES.h
/// @brief AES 加密功能，使用 Crypto++ 开源库
/// @version 1.0
/// @date 2014.12.29
/// @author 圣域天子(Jonix@qtcn.org)
///
/// ====================================================================================================================

#pragma once
#ifndef TIANCHI_TCAES_H
#define TIANCHI_TCAES_H

#ifndef TIANCHI_API
    #define TIANCHI_API
#endif

#include <QByteArray>

class TcAESPrivate;
class TIANCHI_API TcAES
{
public:
    TcAES();
    ~TcAES();

    void        setKey(const QByteArray& key);
    QByteArray  encryp(const QByteArray& data);
    QByteArray  decryp(const QByteArray& data);

private:
    Q_DISABLE_COPY(TcAES);
    Q_DECLARE_PRIVATE(TcAES);
    TcAESPrivate* const d_ptr;
};

#endif // TIANCHI_TCAES_H
