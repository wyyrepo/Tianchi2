/// ********************************************************************************************************************
/// @copyright Tianchi C++ source library for Qt5 (天池共享源码库)\n
/// 天池共享源码库开发组(www.qtcn.org)\n
/// @license 授权协议：请阅读天池共享源码库附带的授权协议(LICENSE.LGPLv2.1)\n
/// ********************************************************************************************************************
/// @file tcCommon.h
/// @brief 一些常用的公共单元。根据 Tianchi 的 common & utils 进行了合并整理
/// @version 1.0
/// @date 2014.12.11
/// @author 圣域天子(Jonix@qtcn.org)
///
/// ====================================================================================================================

#pragma once
#ifndef TIANCHI_TCCOMMON_H
#define TIANCHI_TCCOMMON_H

#ifndef TIANCHI_API
    #define TIANCHI_API
#endif

#include <QString>
#include <QByteArray>
#include <QDateTime>
#include <QJsonValue>

/// @brief 操作模式的标识常量
struct TcOperMode
{
const static int Append = 1; ///< 添加或新建
const static int Change = 2; ///< 修改
const static int Delete = 4; ///< 删除

const static int CopyCell   = 301; ///< 复制一个单元格
const static int CopyCells  = 302; ///< 复制多个单元格
const static int CopyColumn = 303; ///< 复制列
const static int CopyLine   = 304; ///< 复制行
const static int CopyTable  = 305; ///< 复制一张表，默认表示含标题
};

/// @brief 清除一个指针对象
#define TC_FREE(x)  {delete x; x=nullptr;}

/// @brief 分支逻辑判断
inline int iif(bool logic, int v1, int v2=0) { return logic ? v1 : v2; }
/// @brief 分支逻辑判断
inline QString iif(bool logic, const QString& v1, const QString& v2="") { return logic ? v1 : v2; }


/// @brief 转换字符串为日期时间(yyyy/MM/dd HH:mm:ss)
QDateTime TIANCHI_API toDateTime(const QString& text);

/// @brief 转浮点时间值为日期时间(yyyy/MM/dd HH:mm:ss)
QDateTime TIANCHI_API toDateTime(double timeDouble);

/// @brief 返回18位身位证的最后一位校验码
char TIANCHI_API getIDCardVerifyCode(const QByteArray& id);

/// @brief 取编译日期和时间，调用处的代码必须重新编译
QDateTime TIANCHI_API complieDateTime(const QString& complieDate, const QString& complieTime);

/// @brief 分割中文全名中的姓氏、名字和英文名
/// @param full 全名
/// @param sur 姓氏
/// @param real 名字
/// @param english 英文名
/// @return 0: 失败，1: 单姓，2: 复姓，3: 英文名
int TIANCHI_API splitHumanName(const QString& full, QString& sur, QString& real, QString& english);

QByteArray TIANCHI_API md5hex(const QString& str);

// hmac-sha1 带密钥(secret)的哈希算法
QString TIANCHI_API hmacSha1(const QByteArray& baseString, const QByteArray& key);

/// @brief 取 Json 的键值
/// @param [in] jv 把 Json 键值取出后强行转换为 QString 型
QString TIANCHI_API toString(const QJsonValue& jv);
/// @brief 取 Json 的键值
/// @param [in] jv 把 Json 键值取出后强行转换为 QString 型
QString TIANCHI_API toDoubleString(const QJsonValue& jv);
/// @brief 取 Json 的键值
/// @param [in] jv 把 Json 键值取出后强行转换为 QString 型
QString TIANCHI_API toMoneyString(const QJsonValue& jv);
/// @brief 取 Json 的键值
/// @param [in] jv 把 Json 键值取出后强行转换为 int 型
int TIANCHI_API toInt(const QJsonValue& jv);
/// @brief 取 Json 的键值
/// @param [in] jv 把 Json 键值取出后强行转换为 int 型
qint64 TIANCHI_API toInt64(const QJsonValue& jv);
/// @brief 取 Json 的键值
/// @param [in] jv 把 Json 键值取出后强行转换为 double 型
double TIANCHI_API toDouble(const QJsonValue &jv);
/// @brief 取 Json 的键值
/// @param [in] jv 把 Json 键值取出后强行转换为 bool 型
bool TIANCHI_API toBool(const QJsonValue& jv);
/// @brief [in] jv 把 Json 键值取出后判断是否是true值
bool TIANCHI_API isTrue(const QJsonValue& jv);
/// @brief 判断一个字符串是否是boolean的 true值
bool TIANCHI_API isTrue(const QString& s);

/// @brief 把 GBK 转成 Utf-8 编码
QString TIANCHI_API GbkToUtf8(const QByteArray& gbkString);
/// @brief 把 Utf-8 转成 GBK 编码
QByteArray TIANCHI_API Utf8ToGbk(const QString& utf8String);

void DEBUG_TRACE(const char* file, int line, const char* func, const QVariant& text);

#if defined(QT_DEBUG)
  #define TRACE(x)  DEBUG_TRACE(__FILE__, __LINE__, __FUNCTION__, x);
  #define TRACES()  DEBUG_TRACE(__FILE__, __LINE__, __FUNCTION__, "...");
#else
  #define TRACE(x);
  #define TRACES();
#endif
void DEBUG_PRINT(const QVariant& text);
void DEBUG_PRINTLN(const QVariant& text);

inline void PRINT(const QVariant& text) { DEBUG_PRINT(text); }
inline void PRINTLN(const QVariant& text) { DEBUG_PRINTLN(text); }

QByteArray TIANCHI_API cutOff(QByteArray& bytes, const QByteArray& split);

/// @brief 为了缩减长度，把uuid转换为36进制，缩为 12-13 个字符长度
QString TIANCHI_API TcUuidKey(const QString& uuid="");


QByteArray TIANCHI_API TcFirstByteArray(QByteArray& str, const QByteArray& split = "\t");

#endif // TIANCHI_TCCOMMON_H
