/// ********************************************************************************************************************
/// @copyright Tianchi C++ source library for Qt5 (天池共享源码库)\n
/// 天池共享源码库开发组(www.qtcn.org)\n
/// @license 授权协议：请阅读天池共享源码库附带的授权协议(LICENSE.LGPLv2.1)\n
/// ********************************************************************************************************************
/// @file tcExcelReader.h
/// @brief 通过 OLE 方式读取 Microsoft Excel, WPS（Linux 下仅支持WPS）
/// @version 1.0
/// @date 2013.05.02
/// @author XChinux(XChinux@qtcn.org)
/// @attention 需要在安装了 Microsoft Excel 或 WPS 时使用
///
/// ====================================================================================================================

#pragma once
#ifndef TIANCHI_TCEXCELREADER_H
#define TIANCHI_TCEXCELREADER_H

#ifndef TIANCHI_API
    #define TIANCHI_API
#endif

#include <QVariant>
#include <QStringList>

class TcExcelReaderPrivate;

/// @brief simple excel reader class, limit to read first sheet
/// @attention 需要在安装了 Microsoft Excel 或 WPS 时使用
class TIANCHI_API TcExcelReader
{
public:
    TcExcelReader();
    ~TcExcelReader();
    /// @brief  if is null, it can do nothing
    bool isNull() const;
    /// @brief  open excel file, success to return true
    bool open(const QString &file);
    /// @brief  read cell's value
    /// @param [in] rowIndex, index of row, from 1 start
    /// @param [in] columnIndex, index of column, from 1 start
    QVariant cell(int rowIndex, int columnIndex);
    /// @brief  read cell's value
    /// @param [in] colName, column name, from 'a' or 'AB' start
    /// @param [in] rowIndex, index of row, from 1 start
    QVariant cell(const QString &colName, int rowIndex);
    /// @brief  read cell's value
    /// @param [in] cellName, cell's name just like 'A2' or 'ac2'
    QVariant cell(const QString &cellName);

    /// @brief  get sheets count
    int         sheetCount();
    /// @brief  get sheets name list
    QStringList sheetNames();
    /// @brief  set current sheet by index(from 1 start)
    bool        setCurrentSheet(int index);
    /// @brief  set current sheet by name
    bool        setCurrentSheet(const QString &sheetName);
    /// @brief  get current sheet index(from 1 start)
    int         currentSheetIndex();
    /// @brief  get current sheet name
    QString     currentSheetName();

private:
    Q_DISABLE_COPY(TcExcelReader)
    Q_DECLARE_PRIVATE(TcExcelReader)
    TcExcelReaderPrivate* const d_ptr;
};

#endif
