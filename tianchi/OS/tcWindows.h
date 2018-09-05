/// ********************************************************************************************************************
/// @copyright Tianchi C++ source library for Qt5 (天池共享源码库)\n
/// 天池共享源码库开发组(www.qtcn.org)\n
/// @license 授权协议：请阅读天池共享源码库附带的授权协议(LICENSE.LGPLv2.1)\n
/// ********************************************************************************************************************
/// @file tcWindows.h
/// @brief Microsoft Windows 系统功能，只能在Windows上使用
/// @version 1.0
/// @date 2014.12.12
/// @author 渡世白玉(dushibaiyu@yahoo.com)
/// @attention 只能在 Windows 下使用
///
/// ====================================================================================================================

#pragma once
#ifndef TIANCHI_TCWINDOWS_H
#define TIANCHI_TCWINDOWS_H

#ifndef TIANCHI_API
    #define TIANCHI_API
#endif

#include <QtCore>
#if defined(Q_OS_WIN)

#include <QString>
#include <shlobj.h>

/// @brief Microsoft Windows 系统功能，只能在Windows上使用
class TIANCHI_API TcWindows
{
public:
    /// @brief 针对当前登录用户设置 Windows 开机程序启动项，程序名为空时表示删除已存在的启动项
    /// @param name 程序的名称，注册表键值
    /// @param program 程序全路径名，为空时删除已存在的启动项
    static void autoStart(const QString& name, const QString& program="");

    /// @brief 获取系统的路径
    /// @note 常用参数：<br/>
    /// 桌面&emsp;&emsp;CSIDL_DESKTOPDIRECTORY<br/>
    /// 我的文档&emsp;CSIDL_PERSONAL<br/>
    /// 我的图片&emsp;CSIDL_MYPICTURES<br/>
    /// 我的音乐&emsp;CSIDL_MYMUSIC<br/>
    /// 我的视频&emsp;CSIDL_MYVIDEO<br/>
    /// 收藏夹&emsp;CSIDL_FAVORITES<br/>
    /// 发送到&emsp;CSIDL_SENDTO<br/>
    /// 应用程序数据存储&emsp;CSIDL_APPDATA<br/>
    /// 应用程序数据文件夹&emsp;&emsp;CSIDL_LOCAL_APPDATA<br/>
    /// 网络连接的文件夹&emsp;CSIDL_NETHOOD<br/>
    /// 网络打印机的虚拟文件夹&emsp;CSIDL_PRINTHOOD<br/>
    /// 启动目录&emsp;CSIDL_STARTUP<br/>
    /// 开始菜单&emsp;CSIDL_STARTMENU<br/>
    /// 开始程序菜单&emsp;CSIDL_PROGRAMS<br/>
    /// 模板目录&emsp;CSIDL_TEMPLATES<br/>
    /// Internet Explorer的cookie文件夹&emsp;CSIDL_COOKIES<br/>
    /// Inernet Explorer的历史记录文件夹&emsp;CSIDL_HISTORY<br/>
    /// Internet Explorer的Cache文件夹&emsp;CSIDL_INTERNET_CACHE<br/>

    /// Windows文件夹&emsp;CSIDL_WINDOWS<br/>
    /// Windows系统文件夹&emsp;CSIDL_SYSTEM<br/>
    /// 程序文件的文件夹&emsp;CSIDL_PROGRAM_FILES<br/>
    /// 公用系统程序文件夹&emsp;CSIDL_PROGRAM_FILES_COMMON<br/>
    /// 字体目录&emsp;CSIDL_FONTS<br/>
    /// 管理工具目录&emsp;CSIDL_COMMON_ADMINTOOLS<br/>

    /// 公用桌面&emsp;CSIDL_COMMON_DESKTOPDIRECTORY<br/>
    /// 公用文档&emsp;CSIDL_COMMON_DOCUMENTS<br/>
    /// 公用图片&emsp;CSIDL_COMMON_PICTURES<br/>
    /// 公用音乐&emsp;CSIDL_COMMON_MUSIC<br/>
    /// 公用视频&emsp;CSIDL_COMMON_VIDEO<br/>
    /// 公用收藏夹&emsp;CSIDL_COMMON_FAVORITES<br/>
    /// 公用应用程序数据存储&emsp;CSIDL_COMMON_APPDATA<br/>
    /// 公用程序文件夹&emsp;CSIDL_COMMON_PROGRAMS<br/>
    /// 公用开始菜单文件夹&emsp;CSIDL_COMMON_STARTMENU<br/>
    /// 公用启动文件夹&emsp;CSIDL_COMMON_STARTUP<br/>
    /// 公用模块文件夹&emsp;CSIDL_COMMON_TEMPLATES<br/>
    static QString  getWinSysDir(int pathid);

    /// @brief 在指定目录下创建快捷键
    static bool createLink(const QString &fileName, const QString &linkName, const QString &arguments = QString(),
                           const QString &iconPath = QString(),
                           const QString &iconId = QString());//创建快捷方式：源文件，创建到的完整path

    /// @brief 为无框窗口增加缩放功能
    /// @param eventType 对应 nativeEvent(...)参数
    /// @param msg       对应 nativeEvent(...)参数
    /// @param result    对应 nativeEvent(...)参数
    /// @param wndRect   根据需要指定边框的位置，一般用于含阴影的边框，比实际框略小
    /// @code
    /// virtual bool nativeEvent(const QByteArray& eventType, void* msg, long* result) override;
    /// {
    ///     retrun TcWindow::resizeEvent(eventType, msg, result, geometry());
    /// }
    /// @endcode
    static bool resizeEvent(const QByteArray&, void* msg, long* result, const QRect& wndRect);

    static QString  userName();
};

#endif // Q_OS_WIN

#endif // TIANCHI_TCWINDOWS_H
