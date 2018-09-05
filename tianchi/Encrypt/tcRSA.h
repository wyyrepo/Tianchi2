/// ********************************************************************************************************************
/// @copyright Tianchi C++ source library for Qt5 (天池共享源码库)\n
/// 天池共享源码库开发组(www.qtcn.org)\n
/// @license 授权协议：请阅读天池共享源码库附带的授权协议(LICENSE.LGPLv2.1)\n
/// ********************************************************************************************************************
/// @file tcRSA.h
/// @brief RSA 加密功能，使用 Crypto++ 开源库
/// @version 1.0
/// @date 2015.01.19
/// @author 圣域天子(Jonix@qtcn.org)
///
/// ====================================================================================================================

#pragma once
#ifndef TIANCHI_TCRSA_H
#define TIANCHI_TCRSA_H

#ifndef TIANCHI_API
    #define TIANCHI_API
#endif

#include <QByteArray>
#include <string>
using namespace std;

class TcRSAPrivate;
class TIANCHI_API TcRSA
{
public:
    TcRSA();
    ~TcRSA();

    QByteArray  privateKey();
    QByteArray  publicKey();
    void    setKey(const QByteArray& privKey, const QByteArray& pubKey);

    void GenerateKey(unsigned int KeyLength);

    QByteArray  encryp(const QByteArray& data);
    QByteArray  decryp(const QByteArray& data);

private:
    Q_DISABLE_COPY(TcRSA);
    Q_DECLARE_PRIVATE(TcRSA);
    TcRSAPrivate* const d_ptr;
};

#endif // TIANCHI_TCRSA_H
