/// ********************************************************************************************************************
/// @copyright Tianchi C++ source library for Qt5 (天池共享源码库)\n
/// 天池共享源码库开发组(www.qtcn.org)\n
/// @license 授权协议：请阅读天池共享源码库附带的授权协议(LICENSE.LGPLv2.1)\n
/// ********************************************************************************************************************
/// @file tcInvoke.h
/// @brief 映射信号槽的执行对象
/// @version 1.0
/// @date 2014.12.11
/// @author 圣域天子(Jonix@qtcn.org)
///
/// ====================================================================================================================

#pragma once
#ifndef TIANCHI_TCINVOKE_H
#define TIANCHI_TCINVOKE_H

#ifndef TIANCHI_API
    #define TIANCHI_API
#endif

#include <QObject>
#include <QByteArray>

class TIANCHI_API TcInvoke
{
public:
    /// @brief 构造方法
    TcInvoke(QObject* o=nullptr, QByteArray m="")
    {
        init(o, m);
    }
    /// @brief 必要时重置对象的方法
    inline void init(QObject* o, QByteArray m)
    {
        m_object = o;
        m_method = m;
    }

    /// @brief 复制对象
    TcInvoke &operator=(const TcInvoke& from)
    {
        if ( this != &from )
        {
            this->m_object = from.m_object;
            this->m_method = from.m_method;
        }
        return *this;
    }

    /// @brief 以队列方式调用映射方法
    /// @attention 在最初发行时，发现槽方法无法使用 sender() 返回发送信号的对象
    inline bool queued(QGenericArgument val0 = QGenericArgument(0),
                       QGenericArgument val1 = QGenericArgument(),
                       QGenericArgument val2 = QGenericArgument(),
                       QGenericArgument val3 = QGenericArgument(),
                       QGenericArgument val4 = QGenericArgument(),
                       QGenericArgument val5 = QGenericArgument(),
                       QGenericArgument val6 = QGenericArgument(),
                       QGenericArgument val7 = QGenericArgument(),
                       QGenericArgument val8 = QGenericArgument(),
                       QGenericArgument val9 = QGenericArgument())
    {
        try {
            return m_object != nullptr ? m_object->metaObject()->invokeMethod(m_object, m_method,
                                                                           Qt::QueuedConnection,
                                                                           val0, val1, val2, val3, val4,
                                                                           val5, val6, val7, val8, val9)
                                    : false;
        }catch(...)
        {
            return false;
        }
    }

    /// @brief 调用映射方法
    /// @attention 在最初发行时，发现槽方法无法使用 sender() 返回发送信号的对象
    bool invoke(QGenericArgument val0 = QGenericArgument(0),
                       QGenericArgument val1 = QGenericArgument(),
                       QGenericArgument val2 = QGenericArgument(),
                       QGenericArgument val3 = QGenericArgument(),
                       QGenericArgument val4 = QGenericArgument(),
                       QGenericArgument val5 = QGenericArgument(),
                       QGenericArgument val6 = QGenericArgument(),
                       QGenericArgument val7 = QGenericArgument(),
                       QGenericArgument val8 = QGenericArgument(),
                       QGenericArgument val9 = QGenericArgument());

    /// @brief 返回当前对象是否有效？
    /// @return true: 有效，可以进行映射方式的调用
    inline bool isValid() const { return m_object != nullptr && ! m_method.isEmpty(); }

private:
    QObject*    m_object;
    QByteArray  m_method;
};

#endif // TIANCHI_TCINVOKE_H
