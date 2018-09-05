/// ********************************************************************************************************************
/// @copyright Tianchi C++ source library for Qt5 (天池共享源码库)\n
/// 天池共享源码库开发组(www.qtcn.org)\n
/// @license 授权协议：请阅读天池共享源码库附带的授权协议(LICENSE.LGPLv2.1)\n
/// ********************************************************************************************************************
/// @file tcDownloader.h
/// @brief 网络文件下载器，目前仅实现 http 文件下载
/// @version 1.0
/// @date 2013.04.19
/// @author 圣域天子(Jonix@qtcn.org)
///
/// ====================================================================================================================

#pragma once
#ifndef TIANCHI_TCDOWNLOADER_H
#define TIANCHI_TCDOWNLOADER_H

#ifndef TIANCHI_API
    #define TIANCHI_API
#endif

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QFile>

/// @brief 下载文件（或文件的一部分）
class TIANCHI_API TcHttpDownloader : public QObject
{
    Q_OBJECT
public:
    TcHttpDownloader(int index, QObject* parent = 0);
    void start(const QUrl& url, QFile* file, qint64 startPoint=0, qint64 endPoint=-1);

Q_SIGNALS:
    void finished();

public Q_SLOTS:
    void FinishedSlot();
    void HttpReadyRead();

private:
    QNetworkAccessManager   m_Qnam;
    QNetworkReply*          m_Reply;
    QFile*                  m_File;

    const int   m_Index;
    qint64      m_HaveDoneBytes;
    qint64      m_StartPoint;
    qint64      m_EndPoint;

};

/// @brief 管理文件的下载
class TIANCHI_API TcDownloader : public QObject
{
    Q_OBJECT
public:
    TcDownloader(QObject* parent = 0);

    void start(const QString &url, int count);
    qint64 GetFileSize(QUrl url);

Q_SIGNALS:
    void finished();

private Q_SLOTS:
    void SubPartFinished();

private:
    int m_DownloadCount;
    int m_FinishedNum;
    int m_FileSize;
    QUrl m_Url;
    QFile* m_File;
};

#endif // TIANCHI_TCDOWNLOADER_H
