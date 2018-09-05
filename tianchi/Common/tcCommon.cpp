#include "tcCommon.h"

#include <QDebug>

#include <QTextCodec>
#include <QStringList>
#include <QCryptographicHash>

#include <QUuid>
#include <QMutex>
#include <QVariant>
#include <QFileInfo>
#include <iostream>
using namespace std;

QDateTime toDateTime(const QString& text)
{
    QDateTime ret = QDateTime();
    switch(text.length())
    {
    case 23:
        ret.fromString(text, "yyyy-MM-dd HH:mm:ss.zzz");
        break;
    case 19:
        ret.fromString(text, "yyyy-MM-dd HH:mm:ss");
        break;
    case 16:
        ret.fromString(text, "yyyy-MM-dd HH:mm");
        break;
    case 14:
        ret.fromString(text, "yyyyMMddHHmmss");
        break;
    case 10:
        ret.fromString(text, "yyyy-MM-dd");
        break;
    case  8:
        ret.fromString(text, "HH:mm:ss");
        break;
    case  7:
        ret.fromString(text, "yyyy/MM");
        break;
    case  6:
        ret.fromString(text, "HHmmss");
        break;
    case  5:
        if ( text.at(2) == '/'
          || text.at(2) == '-' )
        {
            ret.fromString(text, "MM/dd");
        }else
        if ( text.at(2) == ':' )
        {
            ret.fromString(text, "HH:mm");
        }
        break;
    case  4:
        ret.fromString(text, "yyyy");
        break;
    case  2:
        ret.fromString(text, "dd");
        break;
    case  1:
        ret.fromString(text, "d");
        break;
    }
    return ret;
}

QDateTime toDateTime(double timeDouble)
{
    int    days    = int(timeDouble);
    double seconds = timeDouble - days;

    const static qint64 JULIAN_DAY = 2415019;
    QDate date = QDate::fromJulianDay(JULIAN_DAY + days);
    QTime time(0, 0, 0, 0);
    time = time.addSecs(seconds * 86400.0);
    return QDateTime(date, time);
}

char getIDCardVerifyCode(const QByteArray& id)
{
    char ret = '\0';
    if ( id.length() >= 17 )
    {
        // 加权乘积求和除以11的余数所对应的校验数
        const char verifyMap[] = "10X98765432";
        // 加权因子
        const int factor[] = { 7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2, 1 };

        int Sum = 0;  //加权乘积求和
        for( int i=0;i<17;i++ )
        {
            char c = id[i];

            Sum += (c-'0') * factor[i]; // 加权乘积求和
        }
        ret = verifyMap[Sum % 11]; // 取模
    }
    return ret;
}

QDateTime complieDateTime(const QString& complieDate, const QString& complieTime)
{
    QString DateString = complieDate;
    QString Year  = DateString.right(4);
    QString Month = DateString.left(3).toUpper();
    QString Day   = DateString.mid(4, 2);
    QString TimeString = complieTime;
    QString Hour   = TimeString.left(2);
    QString Minute = TimeString.mid(3, 2);
    QString Second = TimeString.right(2);
    const QString MonthString[12] = { "JAN", "FEB", "MAR", "APR", "MAY", "JUN",
                                      "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"};
    unsigned int MonthValue;
    for( MonthValue=0;MonthValue<sizeof(MonthString);MonthValue++ )
    {
        if ( Month == MonthString[MonthValue] )
        {
            MonthValue++;
            break;
        }
    }
    return QDateTime(QDate(Year.toInt(), MonthValue, Day.toInt()),
                     QTime(Hour.toInt(), Minute.toInt(), Second.toInt()));
}

// 分解姓名（单、复姓、英文）
int splitHumanName(const QString& full, QString& sur, QString& real, QString& english)
{
    QString surs = QTextCodec::codecForLocale()->toUnicode(
                               "欧阳\n太史\n端木\n上官\n司马\n东方\n独孤\n南宫\n万俟\n"
                               "闻人\n夏侯\n诸葛\n尉迟\n公羊\n赫连\n澹台\n皇甫\n宗政\n"
                               "濮阳\n公冶\n太叔\n申屠\n公孙\n慕容\n仲孙\n钟离\n长孙\n"
                               "宇文\n司徒\n鲜于\n司空\n闾丘\n子车\n亓官\n司寇\n巫马\n"
                               "公西\n颛孙\n壤驷\n公良\n漆雕\n乐正\n宰父\n谷梁\n拓跋\n"
                               "夹谷\n轩辕\n令狐\n段干\n百里\n呼延\n东郭\n南门\n羊舌\n"
                               "微生\n公户\n公玉\n公仪\n梁丘\n公仲\n公上\n公门\n公山\n"
                               "公坚\n左丘\n公伯\n西门\n公祖\n第五\n公乘\n贯丘\n公皙\n"
                               "南荣\n东里\n东宫\n仲长\n子书\n子桑\n即墨\n达奚\n褚师\n");
    QStringList doubleSurnames = surs.split("\n");

    QString fullname = full.trimmed();

    int ret = 0;
    if ( ! fullname.isEmpty() )
    {
        if ( fullname.length() != fullname.toLocal8Bit().length() )
        {// 汉字
            foreach(QString s, doubleSurnames)
            {
                if ( ! s.isEmpty() && fullname.startsWith(s) )
                {
                    sur = s;
                    ret = 2;
                    break;
                }
            }
            if ( ret != 2 )
            {
                sur = fullname.mid(0, 1);
                ret = 1;
            }
            real = fullname.mid(sur.length());
        }else
        {// 英文名
            QStringList ss = fullname.split(" ", QString::SkipEmptyParts);
            english = "";
            for( int i=0;i<ss.count();i++ )
            {
                QString t = ss.at(i);
                if ( i == ss.count()-1 )
                {
                    sur = t;
                }else
                {
                    english += t + " ";
                }
            }
            english = english.trimmed();

            ret = 3;
        }
    }
    return ret;
}

QByteArray md5hex(const QString& str)
{
    QCryptographicHash md(QCryptographicHash::Md5);
    md.addData(str.toUtf8());
    return md.result().toHex();
}

QString hmacSha1(const QByteArray& baseString, const QByteArray& key)
{
    const int blockSize = 64;

    QByteArray hmacSha1Key = key.length() > blockSize
            ? QCryptographicHash::hash(key, QCryptographicHash::Sha1)
            : key;

    QByteArray innerPadding(blockSize, char(0x36));
    QByteArray outerPadding(blockSize, char(0x5C));

    for( int i = 0; i < hmacSha1Key.length(); i++ )
    {
        innerPadding[i] = innerPadding[i] ^ hmacSha1Key.at(i);
        outerPadding[i] = outerPadding[i] ^ hmacSha1Key.at(i);
    }

    QByteArray part  = innerPadding;  part .append(baseString);
    QByteArray total = outerPadding;  total.append(QCryptographicHash::hash(part, QCryptographicHash::Sha1));

    QByteArray hashed = QCryptographicHash::hash(total, QCryptographicHash::Sha1);

    QString ret;
    QString s;
    for( int i=0; i<hashed.count(); i++ )
    {
        unsigned char c = hashed.at(i);
        s.sprintf("%02x", c);
        ret += s;
    }
    return ret;
}

QString toString(const QJsonValue& jv)
{
    QString ret = "";
    if ( jv.isDouble() )
    {
        ret = QString::number(jv.toDouble());
    }else
    if ( jv.isString() )
    {
        ret = jv.toString();
    }
    return ret;
}

QString toDoubleString(const QJsonValue& jv)
{
    QString ret = "";
    if ( jv.isDouble() )
    {
        ret = QString::number(jv.toDouble());
    }else
        if ( jv.isString() )
        {
            ret = QString::number(jv.toDouble());
        }else
        {
            ret = "0";
        }
    return ret;
}

QString toMoneyString(const QJsonValue& jv)
{
    QString ret = "";
    if ( jv.isDouble() )
    {
        ret.sprintf( "%.2lf", jv.toDouble( ) );
        return ret;
    } else if ( jv.isString() )
    {
        if ( jv.toString( ).isEmpty( ) ) return "";
        ret.sprintf( "%.2lf", jv.toDouble( ) );
        return ret;
    } else
    {
        ret = "";
        //ret = "0.00";
    }
    return ret;
}

int toInt(const QJsonValue& jv)
{
    int ret = 0;
    if ( jv.isDouble() )
    {
        ret = jv.toDouble();
    }else
    if ( jv.isString() )
    {
        ret = jv.toString().toInt();
    }
    return ret;
}

qint64 toInt64(const QJsonValue &jv)
{
    qint64 ret = 0;
    if ( jv.isDouble() )
    {
        ret = jv.toDouble();
    }else
        if ( jv.isString() )
        {
            ret = jv.toString().toInt();
        }
    return ret;
}

double toDouble(const QJsonValue &jv)
{
    double ret = 0.0;
    if ( jv.isDouble() )
    {
        ret = jv.toDouble();
    }else
        if ( jv.isString() )
        {
            ret = jv.toString().toInt();
        }
    return ret;
}

bool toBool(const QJsonValue& jv)
{
    return isTrue(jv);
}

bool isTrue(const QJsonValue& jv)
{
    bool ret = false;
    if ( jv.isBool() )
    {
        ret = jv.toBool();
    }else
    if ( jv.isDouble() )
    {
        ret = jv.toDouble() >0;
    }else
    if ( jv.isString() )
    {
        ret = isTrue(jv.toString());
    }
    return ret;
}

bool isTrue(const QString& s)
{
    return s.toInt() >0
            || s.compare("true", Qt::CaseInsensitive)==0
            || s.compare("yes", Qt::CaseInsensitive)==0
            || s.compare("ok", Qt::CaseInsensitive)==0
            || s.compare("t", Qt::CaseInsensitive)==0
            || s.compare("y", Qt::CaseInsensitive)==0;
}

QMutex PRINT_MUTEX;
#if defined(QT_DEBUG)
void DEBUG_TRACE(const char* file, int line, const char* func, const QVariant& text)
{

    QFileInfo fi(file);
    PRINT_MUTEX.lock();
    cout<<QDateTime::currentDateTime().toString("yyyy/MM/dd HH:mm:ss.zzz ").toLocal8Bit().data()
       <<fi.completeBaseName().toLocal8Bit().data()
       <<"/"<<func<<"():"<<line<<": "<<text.toString().toLocal8Bit().data()<<endl;
    PRINT_MUTEX.unlock();
}
#else
void DEBUG_TRACE(const char* file, int line, const char* func, const QVariant& text)
{
}
#endif
void DEBUG_PRINT(const QVariant& text)
{
    PRINT_MUTEX.lock();
    cout<<text.toString().toLocal8Bit().data();
    PRINT_MUTEX.unlock();
}
void DEBUG_PRINTLN(const QVariant& text)
{
    PRINT_MUTEX.lock();
    cout<<text.toString().toLocal8Bit().data()<<endl;
    PRINT_MUTEX.unlock();
}

namespace TIANCHI
{
static QTextCodec* tianchi_gbkCodec = QTextCodec::codecForName("GBK");
}
QString GbkToUtf8(const QByteArray& gbkString)
{
    return TIANCHI::tianchi_gbkCodec->toUnicode(gbkString);
}

QByteArray Utf8ToGbk(const QString& utf8String)
{
    return TIANCHI::tianchi_gbkCodec->fromUnicode(utf8String);
}

QByteArray cutOff(QByteArray& bytes, const QByteArray& split)
{
    QByteArray ret;
    int pos = split.isEmpty() ? -1 : bytes.indexOf(split);
    if ( pos > -1 )
    {
        ret = bytes.left(pos);
        bytes.remove(0, pos + split.length());
    }else
    {
        ret = bytes;
        bytes.clear();
    }
    return ret;
}

QString TcUuidKey(const QString& uuid)
{
    QByteArray newUuid = uuid.isEmpty() ? QUuid::createUuid().toByteArray() : uuid.toUtf8();
    newUuid.replace("{", "");
    newUuid.replace("-", "");
    newUuid.replace("}", "");

    quint64 total = 0;
    for( int i=0; i<newUuid.count(); i++ )
    {
        total *= 10;
        total += int(newUuid.at(i));
    }

    const char* Carry = "0123456789abcdefghijklmnopqrstuvwxyz";

    QString ret;
    while(total >0)
    {
        ret = QString(Carry[total % 36]) + ret;
        total /= 36;
    }
    return ret;
}

QByteArray TcFirstByteArray(QByteArray& str, const QByteArray& split)
{
    QByteArray ret;
    int endOf = str.indexOf(split);
    if ( endOf == 0 )
    {
        str.remove(0, 1);
    }
    else
    if ( endOf > 0 )
    {
        ret = str.left(endOf);
        str.remove(0, endOf +1);
    }
    else
    {
        ret = str;
    }

    return ret;
}
