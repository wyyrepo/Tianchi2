/// ********************************************************************************************************************
/// @copyright Tianchi C++ source library for Qt5 (天池共享源码库)\n
/// 天池共享源码库开发组(www.qtcn.org)\n
/// @license 授权协议：请阅读天池共享源码库附带的授权协议(LICENSE.LGPLv2.1)\n
/// ********************************************************************************************************************
/// @file tcTextToSpeech.h
/// @brief 文字转为语音进行播放，仅限 Windows 下使用
/// @version 1.0
/// @date 2013.04.06
/// @author 圣域天子(Jonix@qtcn.org)
///
/// ====================================================================================================================

#pragma once
#ifndef TIANCHI_TCTEXTTOSPEECH_H
#define TIANCHI_TCTEXTTOSPEECH_H

#ifndef TIANCHI_API
    #define TIANCHI_API
#endif

#include <QThread>
#include <QString>
#include <QMutex>

/// @brief 文字转为语音进行播放，仅限 Windows 下使用
class TIANCHI_API TcTextToSpeech : public QThread
{
public:
    /// @brief 阻塞方式播放文字语音
    static void play(const QString& text);

    /// @brief 线程方式播放文字语音，多语音时排队播放
    void playing(const QString& text);

protected:
    virtual void run() override;

    QMutex          m_mutex;
    QList<QString>  m_sounds;
};

#endif // TIANCHI_TCTEXTTOSPEECH_H

