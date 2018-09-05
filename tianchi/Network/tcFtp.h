/// ********************************************************************************************************************
/// @copyright Tianchi C++ source library for Qt5 (天池共享源码库)\n
/// 天池共享源码库开发组(www.qtcn.org)\n
/// @license 授权协议：请阅读天池共享源码库附带的授权协议(LICENSE.LGPLv2.1)\n
/// ********************************************************************************************************************
/// @file tcFtp.h
/// @brief FTP 操作
/// @version 1.0
/// @date 2013.04.19
/// @author 圣域天子(Jonix@qtcn.org)
///
/// ====================================================================================================================

#pragma once
#ifndef TIANCHI_TCFTP_H
#define TIANCHI_TCFTP_H

#ifndef TIANCHI_API
    #define TIANCHI_API
#endif

#include <QTcpServer>
#include <QTcpSocket>
#include <QFile>

class TIANCHI_API TcFtp : public QObject
{
     Q_OBJECT
public:
    enum Mode {PASV,PORT};
    enum Type {BINARY='I',ASCII='A',EBCDIC='E',LOCAL='L'};
    enum CMD{CMD_PUT,CMD_GET,CMD_LIST,CMD_OTHER};

public:
    explicit TcFtp(QString ip, quint16 port, QString username, QString passwd);
    explicit TcFtp();
    ~TcFtp();
    void login(QString username, QString passwd);
    bool connectToHost(QString ip,quint16 port);
    void mode(Mode transfer_mode){m_mode=transfer_mode;}
    void type(Type transfer_type){m_type=transfer_type;}
    void put(QString local_filename, QString remote_filename, qint64 offset=0, bool is_append=false);
    void get(QString local_filename,QString remote_filename,qint64 offset=0);
    qint64 fileSize(QString remote_filename);
    void list(QString remote_dir);
    void rawCommand(QString cmd);
    bool connectStatus(){return b_isConnected;}
    bool loginStatus(){return b_isLogined;}

private:
    void setTransferProperty();
    void addDataChannel();

private:
    QString str_ip;
    quint16 n_port;
    QString str_username;
    QString str_password;
    Mode m_mode;
    Type m_type;
    CMD m_cmdType;

    bool b_isConnected;
    bool b_isLogined;
    bool b_stop;

    QByteArray m_data;
    QTcpSocket *p_cmdSocket;
    QTcpSocket *p_dataSocket;
    QTcpServer *p_listener;

    QFile *p_file;
    qint64 n_transferValue;
    qint64 n_transferTotal;
    qint64 n_remoteFileSize;

    const QString LINE_CR;

signals:
    void failToDataChannel();
    void loginSuccess();
    void execCmdResult(QString result);
    void transferDataProgress(qint64 transfer_size,qint64 total_size);
    void transferFinished();
    void error(int code,QString desc);
    void remoteDirInfo(QStringList dirInfo);
    void logout();

public slots:
    void connectError(QAbstractSocket::SocketError code);
    void stopTransfer(){b_stop=true;}
private slots:
    void connected();
    void readCmdResult();
    void getPORTSocket();
    void writeData();
    void readData();
    void readDataFinished();
    void transferData();
    void readDirInfo();
    void clearDataSocket();
};

#endif // TIANCHI_TCFTP_H
