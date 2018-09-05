#include "tcUdp.h"

#include <QByteArray>

TcUdp::TcUdp()
    : QUdpSocket()
{
    m_recvObject = NULL;
}

TcUdp::~TcUdp()
{
    close();
}

int TcUdp::start(int Port)
{
    close();
    //if ( bind(Port, QUdpSocket::ShareAddress) )
    if ( bind(Port) )
    {
        connect(this, SIGNAL(readyRead()), this, SLOT(udpRecv()));
    }
    return isValid() ? localPort() : 0;
}



void TcUdp::udpRecv()
{
    while( hasPendingDatagrams() )
    {
        QByteArray datagram;
        datagram.resize(pendingDatagramSize());
        QHostAddress client;
        readDatagram(datagram.data(), datagram.size(), &client);

        if ( m_recvObject != NULL
          && m_recvObject->metaObject()->invokeMethod(m_recvObject, m_recvMethod.data(),
                                                      Q_ARG(TcUdp*, this),
                                                      Q_ARG(QHostAddress, client),
                                                      Q_ARG(QByteArray, datagram)) )
        {
        }else
        {
            Q_EMIT udpMessage(client, datagram);
        }
    }
}

bool TcUdp::sendMessage(QHostAddress Host, int Port, const QByteArray& S)
{
    qint64 len = S.size();
    return writeDatagram(S.constData(), S.size(), Host, Port) == len;
}

void TcUdp::sendBroadcast(int Port, const QByteArray& S)
{
    writeDatagram(S, QHostAddress::Broadcast, Port);
}

