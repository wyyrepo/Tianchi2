/// ********************************************************************************************************************
/// @copyright Tianchi C++ source library for Qt5 (天池共享源码库)\n
/// 天池共享源码库开发组(www.qtcn.org)\n
/// @license 授权协议：请阅读天池共享源码库附带的授权协议(LICENSE.LGPLv2.1)\n
/// ********************************************************************************************************************
/// @file tcUdp.h
/// @brief Udp协议的发送以及接收服务器
/// @version 1.0
/// @date 2014.12.11
/// @author 圣域天子(Jonix@qtcn.org)
///
/// ====================================================================================================================

#pragma once
#ifndef TIANCHI_TCUDP_H
#define TIANCHI_TCUDP_H

#ifndef TIANCHI_API
    #define TIANCHI_API
#endif

#include <QUdpSocket>

/// @brief UDP 协议的通讯器
class TIANCHI_API TcUdp : public QUdpSocket
{
    Q_OBJECT
    typedef QUdpSocket inherited;
public:
    TcUdp();
    virtual ~TcUdp();

    /// @brief 启动为可接收Udp信息的服务器
    /// @param Port 端口号，0表示由系统随机开启一个端口
    /// @return 返回启动成功的端口号。0表示启动失败，如端口已被占用
    int start(int Port=0);

    /// @brief 关闭Udp服务器
    inline bool stop() { return isValid() ? close(), true : false; }

    /// @brief 向指定的服务器和端口发送字符集。不需要启动为服务器
    /// @return 发送是否成功
    bool    sendMessage(QHostAddress Host, int Port, const QByteArray& S);
    /// @brief 向指定的服务器和端口发送字符集。不需要启动为服务器
    /// @return 发送是否成功
    inline bool sendMessage(QHostAddress Host, int Port, const char* S)
                           { return sendMessage(Host, Port, QByteArray(S)); }
    /// @brief 向指定的服务器和端口发送字符串。不需要启动为服务器
    /// @return 发送是否成功
    inline bool sendMessage(QHostAddress Host, int Port, const QString& S)
                           { return sendMessage(Host, Port, S.toUtf8()); }
    /// @brief 向指定的端口发送广播字符集。不需要启动为服务器
    void    sendBroadcast(int port, const QByteArray& S);
    /// @brief 向指定的端口发送广播字符集。不需要启动为服务器
    inline void sendBroadcast(int port, const char* S)
                             { sendBroadcast(port, QByteArray(S)); }
    /// @brief 向指定的端口发送广播字符串。不需要启动为服务器
    inline void sendBroadcast(int Port, const QString& S)
                             { return sendBroadcast(Port, S.toUtf8()); }

    /// @brief 设置回调方法，优先于 signals 的接收方式
    /// @warning 接收槽的函数原型为 void recv(TcUdp*, const QHostAddress&, const QByteArray&);
    inline void setRecvMethod(QObject* RecvObject, const QByteArray& RecvMethod)
                             { m_recvObject = RecvObject; m_recvMethod = RecvMethod; }

Q_SIGNALS:
    /// @brief 设置信号接收槽，只有回调方法未设置时才有效
    void udpMessage(const QHostAddress& Client, const QByteArray& Datagram);

protected slots:
    void udpRecv();

protected:
    QObject*    m_recvObject;
    QByteArray  m_recvMethod;
};

#endif // TIANCHI_TCUDP_H
