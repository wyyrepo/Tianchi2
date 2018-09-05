#include "tcFtp.h"

#include <QHostAddress>
#include <QFileInfo>
#include <QThread>

TcFtp::TcFtp()
    : QObject(0)
    , b_isConnected(false)
    , b_isLogined(false)
    , LINE_CR("\r\n")
{
    p_cmdSocket=new QTcpSocket;
    p_dataSocket=nullptr;
    p_listener=new QTcpServer;
    m_mode=TcFtp::PORT;
    m_type=TcFtp::BINARY;
    m_cmdType=TcFtp::CMD_OTHER;
    p_file=new QFile;
    n_transferValue=0;
    n_transferTotal=0;
    n_remoteFileSize=0;
    b_stop=false;
}

TcFtp::TcFtp(QString ip,quint16 port,QString username,QString passwd)
    : QObject(0)
    , b_isConnected(false)
    , b_isLogined(false)
{
    p_cmdSocket=new QTcpSocket;
    p_dataSocket=nullptr;
    p_listener=new QTcpServer;
    m_mode=TcFtp::PORT;
    m_type=TcFtp::BINARY;
    m_cmdType=TcFtp::CMD_OTHER;
    p_file=new QFile;
    n_transferValue=0;
    n_transferTotal=0;
    n_remoteFileSize=0;
    b_stop=false;
    str_ip=ip;
    n_port=port;
    str_username=username;
    str_password=passwd;

    if(!connectToHost(str_ip,n_port))
        return;

    login(str_username,str_password);
}

TcFtp::~TcFtp()
{
    delete p_cmdSocket;
    delete p_listener;
    delete p_file;
}

void TcFtp::setTransferProperty()
{
    QString cmd="TYPE "+QString(m_type)+LINE_CR;
    p_cmdSocket->write(cmd.toLatin1());
}

void TcFtp::login(QString username,QString passwd)
{
    if(!b_isConnected)
        return;

    QString cmd="USER "+username+LINE_CR+"PASS "+passwd+LINE_CR;

    p_cmdSocket->write(cmd.toLatin1());

    //prepare receive all response data
    connect(p_cmdSocket,SIGNAL(readyRead()),this,SLOT(readCmdResult()),Qt::UniqueConnection);
    //set global transfer property
    setTransferProperty();
    connect(p_listener,SIGNAL(newConnection()),this,SLOT(getPORTSocket()));
}

bool TcFtp::connectToHost(QString ip, quint16 port)
{
    p_cmdSocket->connectToHost(ip,port);
    connect(p_cmdSocket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(connectError(QAbstractSocket::SocketError)));
    connect(p_cmdSocket,SIGNAL(connected()),this,SLOT(connected()));

    //block way run
    if(!p_cmdSocket->waitForConnected())
        b_isConnected=false;

    return b_isConnected;
}

void TcFtp::addDataChannel()
{
    QString cmd="";
    if(m_mode==TcFtp::PORT)
    {
        QHostAddress host(str_ip);
        if(p_listener->isListening())
            p_listener->close();
        if(!p_listener->listen(host,0)){
            emit failToDataChannel();
            return;
        }

        quint16 port=p_listener->serverPort();
        quint32 ipVal=host.toIPv4Address();
        QString address=QString::number((ipVal&0xff000000)>>24)+QChar(',')+QString::number((ipVal&0xff0000)>>16)+QChar(',')+QString::number((ipVal&0xff00)>>8)+QChar(',')+QString::number(ipVal&0xff);
        address+=QChar(',')+QString::number((port&0xff00)>>8)+QChar(',')+QString::number(port&0xff);
        cmd="PORT "+address+LINE_CR;
        p_cmdSocket->write(cmd.toLatin1());
    }else
    {
        cmd="PASV"+LINE_CR;
        p_cmdSocket->write(cmd.toLatin1());
    }
}

void TcFtp::getPORTSocket()
{
    p_dataSocket=p_listener->nextPendingConnection();
    //start transfer data
    transferData();
}

void TcFtp::put(QString local_filename,QString remote_filename,qint64 offset,bool is_append)
{
    if(!b_isLogined || p_dataSocket!=nullptr)
        return;

    addDataChannel();

    QFileInfo info(local_filename);
    if(!info.exists() || !info.isReadable()){
        emit error(11,"can`t read local file!");
        return;
    }

    if(p_file->isOpen())
        p_file->close();

    p_file->setFileName(local_filename);
    if(!p_file->open(QIODevice::ReadOnly)){
        emit error(11,p_file->errorString());
        return;
    }

    QString cmd="ALLO "+QString::number(info.size()-offset)+LINE_CR;
    if(is_append)
        cmd+="APPE "+remote_filename+LINE_CR;
    if(offset>0)
        cmd+="REST "+QString::number(offset)+LINE_CR;

    cmd+="STOR "+remote_filename+LINE_CR;

    n_transferValue=offset;
    n_transferTotal=info.size();
    b_stop=false;
    p_file->seek(offset);
    m_cmdType=TcFtp::CMD_PUT;
    p_cmdSocket->write(cmd.toLatin1());
}

void TcFtp::get(QString local_filename,QString remote_filename,qint64 offset)
{
    if(!b_isLogined || p_dataSocket!=nullptr)
        return;

    qint64 remoteFileSize=fileSize(remote_filename);
    if(remoteFileSize<=0)
        return;

    addDataChannel();

    if(p_file->isOpen())
        p_file->close();

    p_file->setFileName(local_filename);
    if(!p_file->open(QIODevice::WriteOnly)){
        emit error(11,p_file->errorString());
        return;
    }

    QString cmd="";
    if(offset>0)
        cmd+="REST "+QString::number(offset)+LINE_CR;

    cmd+="RETR "+remote_filename+LINE_CR;

    n_transferValue=offset;
    n_transferTotal=remoteFileSize;
    b_stop=false;
    m_cmdType=TcFtp::CMD_GET;
    p_cmdSocket->write(cmd.toLatin1());
}

void TcFtp::list(QString remote_dir)
{
    if(!b_isLogined || p_dataSocket!=nullptr)
        return;

    addDataChannel();

    QString cmd="LIST "+remote_dir+LINE_CR;

    m_cmdType=TcFtp::CMD_LIST;
    p_cmdSocket->write(cmd.toLatin1());
}

void TcFtp::rawCommand(QString cmd)
{
    if(!b_isLogined || cmd.length()<=0)
        return;

    m_cmdType=TcFtp::CMD_OTHER;
    p_cmdSocket->write(cmd.toLatin1());
}

qint64 TcFtp::fileSize(QString remote_filename)
{
    if(!b_isLogined || remote_filename.length()<=0)
        return 0;

    n_remoteFileSize=0;
    QString cmd="SIZE "+remote_filename+LINE_CR;
    if(p_cmdSocket->write(cmd.toLatin1())<=0 || !p_cmdSocket->waitForReadyRead())
        return 0;

    return n_remoteFileSize;
}

void TcFtp::connectError(QAbstractSocket::SocketError code)
{
    switch(code){
    case QTcpSocket::ConnectionRefusedError:
        emit error(0,"connect resfuse error!");
        break;
    case QTcpSocket::RemoteHostClosedError:
        emit error(1,"remote host closed!");
        break;
    case QTcpSocket::HostNotFoundError:
        emit error(2,"host not found!");
        break;
    case QTcpSocket::SocketTimeoutError:
        emit error(3,"connect timeout!");
        break;
    case QTcpSocket::NetworkError:
        emit error(4,"network error!");
        break;
    default:
        emit error(code,"unkown error,please check tcp socket!");
    }

    b_isConnected=false;
}

void TcFtp::connected()
{
    b_isConnected=true;
}

void TcFtp::readCmdResult()
{
    QByteArray data;

    while((data=p_cmdSocket->readLine()).length()>0){
        qDebug()<<data;
        QString result=QString(data);
        QRegExp regexp("^\\d{3}\.+");

        if(!regexp.exactMatch(result))
            continue;

        QStringList strlist=result.split(' ');
        bool toInt=false;
        int code=strlist.first().toInt(&toInt);
        if(!toInt)
            continue;

        switch(code){
            case 230://login success
                emit loginSuccess();
                b_isLogined=true;
                break;
            case 227:{ //build pasv data channel
                    QRegExp regexp("\(?:(\\d{1,3}),(\\d{1,3}),(\\d{1,3}),(\\d{1,3}),(\\d{1,3}),(\\d{1,3})\)");
                    QString ip;quint16 port;
                    if(regexp.indexIn(result)!=-1){
                        ip=regexp.cap(1)+"."+regexp.cap(2)+"."+regexp.cap(3)+"."+regexp.cap(4);
                        port=(regexp.cap(5).toUInt()<<8)+regexp.cap(6).toUInt();
                    }

                    //add new data connect,(old connect ignore)
                    p_dataSocket=new QTcpSocket;
                    p_dataSocket->connectToHost(QHostAddress(ip),port);
                    if(!p_dataSocket->waitForConnected()){
                        emit failToDataChannel();
                        return;
                    }

                    //start transfer data
                    transferData();
                }
                break;
           case 213:{
                bool toInt=false;
                qint64 size=strlist.last().toLongLong(&toInt);
                if(toInt && size>0)
                    n_remoteFileSize=size;
                }break;
            case 421://FTP timeout
                b_isConnected=false;
                b_isLogined=false;
                emit logout();
                break;
            default:
                break;
        }

        emit execCmdResult(result);
    }
}

void TcFtp::transferData()
{
    if(p_dataSocket==nullptr)
        return;

    switch(m_cmdType)
    {
    case TcFtp::CMD_GET:
        //prepare to download
        connect(p_dataSocket,SIGNAL(readyRead()),this,SLOT(readData()));
        connect(p_dataSocket,SIGNAL(readChannelFinished()),this,SLOT(readDataFinished()));
        break;
    case TcFtp::CMD_PUT:
        //prepare to upload
        connect(p_dataSocket,SIGNAL(bytesWritten(qint64)),this,SLOT(writeData()));
        writeData();
        break;
    case TcFtp::CMD_LIST:
        //read dir info
        connect(p_dataSocket,SIGNAL(readyRead()),this,SLOT(readDirInfo()));
        break;
    default:
        break;
    }

    //clear data socket connect
    connect(p_dataSocket,SIGNAL(disconnected()),this,SLOT(clearDataSocket()));
}

void TcFtp::clearDataSocket()
{
    if ( p_dataSocket != nullptr )
    {
        p_dataSocket->close();
        delete p_dataSocket;
    }
    p_dataSocket=nullptr;
}

void TcFtp::readDirInfo()
{
    if(m_cmdType!=TcFtp::CMD_LIST)
        return;

    QStringList dirInfo;
    while(p_dataSocket->bytesAvailable()>0){
        QString info=QString(p_dataSocket->readLine());
        if(info.length()<=0)
            continue;

        dirInfo.append(info);
    }

    emit remoteDirInfo(dirInfo);
    clearDataSocket();
}

void TcFtp::readDataFinished()
{
    p_file->close();

    clearDataSocket();
    emit transferFinished();
    return;
}

void TcFtp::readData()
{
    if(m_cmdType!=TcFtp::CMD_GET)
        return;

    int bufsize=8*1024;//write size 8KB
    p_dataSocket->setReadBufferSize(bufsize*16);//socket buffer size 128KB

    while(p_dataSocket->bytesAvailable()>0){
        QByteArray data=p_dataSocket->read(bufsize);
        if(b_stop){
            readDataFinished();
            return;
        }

        qint64 bytesWrite=p_file->write(data);
        if(bytesWrite==-1){
            emit error(12,"write to file fail!");
            p_file->close();
            clearDataSocket();
            return;
        }

        n_transferValue+=bytesWrite;
        emit transferDataProgress(n_transferValue,n_transferTotal);
    }
}

void TcFtp::writeData()
{
    if(!p_file->isOpen())
        return;

    const int bufsize=8*1024;
    char buffer[bufsize];
    qint64 read=p_file->read(buffer, bufsize);
    if(read==-1){
        emit error(11,"can't read file!");
        p_file->close();
        clearDataSocket();
        return;
    }

    if(read==0 || b_stop){
        p_file->close();
        clearDataSocket();
        emit transferFinished();
        return;
    }

    if(read>0){
        qint64 bytesWrite=p_dataSocket->write(buffer,bufsize);
        if(bytesWrite==0){
            clearDataSocket();
            emit error(21,"write to server fail!");
            return;
        }

        n_transferValue+=bytesWrite;
        emit transferDataProgress(n_transferValue,n_transferTotal);
    }
}
