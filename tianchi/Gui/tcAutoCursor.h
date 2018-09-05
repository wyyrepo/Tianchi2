/// ********************************************************************************************************************
/// @copyright Tianchi C++ source library for Qt5 (天池共享源码库)\n
/// 天池共享源码库开发组(www.qtcn.org)\n
/// @license 授权协议：请阅读天池共享源码库附带的授权协议(LICENSE.LGPLv2.1)\n
/// ********************************************************************************************************************
/// @file tcAutoCursor.h
/// @brief 鼠标光标的设置和自动恢复处理
/// @version 1.1
/// @date 2014.12.11
/// @author 圣域天子(Jonix@qtcn.org)
///
/// ====================================================================================================================

#pragma once
#ifndef TIANCHI_TCAUTOCURSOR_H
#define TIANCHI_TCAUTOCURSOR_H

#ifndef TIANCHI_API
    #define TIANCHI_API
#endif

#include <QtCore>
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
  #include <QGuiApplication>
#else
  #include <QApplication>
#endif

#include <QCursor>

/// @brief 光标形态变化类的根类.(一般不直接使用)
/// @see class TcCursorWait
/// @see class TcCursorBusy
class TIANCHI_API TcAutoCursor
{
public:
    /// @brief 立即恢复最初的光标
    inline void restore()
    {
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
        QGuiApplication::restoreOverrideCursor();
#else
        QApplication::restoreOverrideCursor();
#endif
    }

protected:
    explicit TcAutoCursor(Qt::CursorShape shape)
    {
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
        QGuiApplication::setOverrideCursor(QCursor(shape));
#else
        QApplication::setOverrideCursor(QCursor(shape));
#endif
    }
    virtual ~TcAutoCursor()
    {
        restore();
    }
    QCursor  m_cursor;
};

/// @brief 表示忙的等待沙漏光标
/// @par 示例:
/// @code
/// void myForm::onClick()
/// {
///     TcCursorWait wait; // 自动变成等待光标
///
///     ... 处理代码 ...
///
/// } // 退出块时，wait 被释放，使光标自动恢复为原先的光标形态
/// @endcode
/// @see class TcCursorBusy
class TIANCHI_API TcCursorWait : public TcAutoCursor
{
public:
    explicit TcCursorWait()
        : TcAutoCursor(Qt::WaitCursor)
    {
    }
};

/// @brief 表示后台忙的等待沙漏光标
/// @par 示例:
/// @code
/// void myForm::onClick()
/// {
///     TcCursorBusy busy; // 自动变成后台忙光标
///
///     ... 处理代码 ...
///
///
/// } // 退出块时，busy 被释放，使光标自动恢复为原先的光标形态
/// @endcode
/// @see class TcCursorWait
class TIANCHI_API TcCursorBusy : public TcAutoCursor
{
public:
    explicit TcCursorBusy()
        : TcAutoCursor(Qt::BusyCursor)
    {
    }
};

#endif // TIANCHI_TCAUTOCURSOR_H
