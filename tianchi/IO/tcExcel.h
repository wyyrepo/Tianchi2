/// ********************************************************************************************************************
/// @copyright Tianchi C++ source library for Qt5 (天池共享源码库)\n
/// 天池共享源码库开发组(www.qtcn.org)\n
/// @license 授权协议：请阅读天池共享源码库附带的授权协议(LICENSE.LGPLv2.1)\n
/// ********************************************************************************************************************
/// @file tcExcel.h
/// @brief 通过 OLE 方式操作 Microsoft Excel（仅限 Windows 下使用，要求已安装 Excel）
/// @version 1.0
/// @date 2013.04.10
/// @author 圣域天子(Jonix@qtcn.org)
/// @attention 只能在 Windows 下，并已安装了 Microsoft Excel 时使用
///
/// ====================================================================================================================

#pragma once
#ifndef TIANCHI_TCEXCEL_H
#define TIANCHI_TCEXCEL_H

#include <QtCore>
#if defined(Q_OS_WIN)

#ifndef TIANCHI_API
    #define TIANCHI_API
#endif

#include <QString>
#include <QStringList>
#include <QVariant>
#include <ActiveQt/QAxObject>

/// @class TcExcel 通过 OLE 方式操作 Microsoft Excel
/// @brief 通过 OLE 方式操作 Microsoft Excel
/// @note 通过 OLE 方式操作 Microsoft Excel
/// @warning 只能在 Windows 下，并已安装了 Excel 时才能使用
class TIANCHI_API TcExcel
{
public:
    /// @brief 构造方法
    TcExcel();
    /// @brief 析构方法
    virtual ~TcExcel();

    /// @brief 设置方向的常数
    enum Alignment
    {
        xlTop    = -4160, ///< 靠上
        xlLeft   = -4131, ///< 靠左
        xlRight  = -4152, ///< 靠右
        xlCenter = -4108, ///< 居中
        xlBottom = -4107  ///< 靠下
    };

    /// @brief 创建一个Microsoft Excel文件
    bool create(const QString& filename = QString());
    /// @brief 打开一个Microsoft Excel文件
    bool open(const QString& filename = QString());
    /// @brief 保存Microsoft Excel文件
    void save(const QString& filename = QString());
    /// @brief 关闭Microsoft Excel文件
    void close();
    /// @brief 踢出当前打开的 Microsoft Excel<br>
    /// @brief 放弃此对象对该 Excel 的控制权<br>
    /// @brief Excel 文件仍保持打开，但丧失了控制权
    void kick();

    /// @brief 设置当前打开的 Excel 是否可见
    void setVisible(bool value);
    /// @brief 设置 Excel 文档的标题
    void setCaption(const QString& value);

    /// @brief 新建一本 Excel 文档
    bool addBook();

    /// @brief 返回当前 Excel 的 Sheet 数量
    int sheetCount();

    /// @brief 返回当前打开的 Excel 全部 Sheet 名
    QStringList sheetNames();

    /// @brief 返回当前 Sheet.
    bool currentSheet();

    /// @brief 设置并指定当前 Sheet.
    /// @param [in] 当前 Sheet 索引，从 1 开始
    bool setCurrentSheet(int index);

    /// @brief 当前打开的 Excel 的 Sheet 名
    inline QString currentSheetName() const { return m_sheetName; }

    /// @brief 读取单元格 Sheet 的内容
    /// @param [in] row 行号，从 1 开始
    /// @param [in] col 列号，从 1 开始
    /// @return 返回指定单元格的内容
    QVariant read(int row, int col);

    /// @brief 读取单元格 Sheet 的内容
    /// @param [in] row 行号，从 1 开始
    /// @param [in] col 列号，从 1 开始
    /// @return 返回指定单元格的内容
    inline QVariant cell(int row, int col) { return read(row, col); }

    /// @brief 写入单元格 Sheet 的内容
    /// @param [in] row 行号，从 1 开始
    /// @param [in] col 列号，从 1 开始
    /// @param [in] value 准备写入的内容
    void write(int row, int col, const QVariant& value);

    /// @brief 对指定单元进行格式化
    /// @param [in] row 行号，从 1 开始
    /// @param [in] col 列号，从 1 开始
    /// @param [in] format 格式化字符串
    void cellFormat(int row, int col, const QString& format);

    /// @brief 对指定单元设置对齐方式
    /// @param [in] row 行号，从 1 开始
    /// @param [in] col 列号，从 1 开始
    /// @param [in] hAlign 横向对齐方式
    /// @param [in] vAlign 竖向对齐方式
    void cellAlign(int row, int col, Alignment hAlign, Alignment vAlign);

    /// @brief 获取有效区域信息
    /// @see rowStart() const
    /// @see rowEnd() const
    /// @see colStart() const
    /// @see colEnd() const
    bool usedRange(int& rowStart, int& colStart, int &rowEnd, int &colEnd);

private:
    QAxObject*  excel ;
    QAxObject*  books ;
    QAxObject*  book  ;
    QAxObject*  sheets;
    QAxObject*  sheet ;

    QString     m_filename;
    QString     m_sheetName;

    void construct();
    void destory();
};
#endif // Q_OS_WIN
#endif // TIANCHI_EXCEL_H
