#include "tcHttp.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QEventLoop>
#include <QTimer>

#include <iostream>
using namespace std;

TcHttp::TcHttp(int timeout)
    : m_timeout(timeout)
{

}

QByteArray TcHttp::get(const QString& url)
{
    QNetworkAccessManager   nam;
    QEventLoop loop;
    QNetworkReply* reply = nam.get(QNetworkRequest(QUrl(url)));
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()), Qt::DirectConnection);
    QTimer::singleShot(m_timeout, &loop, SLOT(quit()));
    loop.exec();

    return reply->readAll();
}

QByteArray TcHttp::post(const QString& url, const QByteArray& content)
{
    QEventLoop loop;
    QNetworkRequest req;
    req.setUrl(QUrl(url));
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    req.setHeader(QNetworkRequest::ContentLengthHeader, content.length());
    QNetworkAccessManager   nam;
    QNetworkReply* reply = nam.post(req, content);
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()), Qt::DirectConnection);
    QTimer::singleShot(m_timeout, &loop, SLOT(quit()));
    loop.exec();

    return reply->readAll();
}

