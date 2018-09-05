/// ********************************************************************************************************************
/// @copyright Tianchi C++ source library for Qt5 (天池共享源码库)\n
/// 天池共享源码库开发组(www.qtcn.org)\n
/// @license 授权协议：请阅读天池共享源码库附带的授权协议(LICENSE.LGPLv2.1)\n
/// ********************************************************************************************************************
/// @file tcIO.h
/// @brief 目录、文件等操作功能
/// @version 1.1
/// @date 2014.12.11
/// @author 南果梨(cnhemiya@gmail.com)
///
/// ====================================================================================================================

#pragma once
#ifndef TIANCHI_TCIO_H
#define TIANCHI_TCIO_H

#ifndef TIANCHI_API
    #define TIANCHI_API
#endif

#include <QObject>
#include <QStringList>

/// @author 南果梨 cnhemiya@gmail.com
/// @date 2013-04-21
class TIANCHI_API TcIO : public QObject
{
    Q_OBJECT
public:
    explicit TcIO(QObject* parent = 0);

    /// @brief 默认的缓冲大小 4MB
    static const int defaultBufferSize;

    /// @brief 1KB = 1024
    static const int KB = 1024;

    /// @brief 1MB = 1024 * 1024 = 1048576
    static const int MB = 1048576;

    /// @brief 1GB = 1024 * 1024 * 1024 = 1073741824
    static const int GB = 1073741824;

    /// @brief 装载文本文件,参数codec指定读取的编码,若为空,则不预设
    static bool loadFromFile(QString& context, const QString &filename, const QString &codec = QString());

    /// @brief 装载二进制文件
    static bool readFileContent(QByteArray& context, const QString &filename);

    /// @brief 在指定目录中返回一个临时文件名
    /// @return 返回临时文件名，注意不创建该文件
    /// @note 此方法不会自动创建文件
    static QString uniqueFileName(const QString &dir, const QString &fileTemplate, const QString &suffix= QString());

    /// @brief 取执行文件的版本，仅支持 Windows
    /// @param [in] exeFile 包含版本信息的文件名(.exe, .dll等)
    /// @return 版本信息(xxx.xxx.xxx.xxx)
    static QString fileVersion(const QString& exeFile);

    /// @brief 取执行文件的版本，仅支持 Windows
    /// @param [in] exeFile 包含版本信息的文件名(.exe, .dll等)
    /// @param [out] vMajor  主版本号
    /// @param [out] vMinor  副版本号
    /// @param [out] Release 发布号
    /// @param [out] vBuild  编译号
    /// @return 版本信息(xxx.xxx.xxx.xxx)
    static QString fileVersion(const QString& exeFile, int& vMajor, int& vMinor, int& Release, int& vBuild);

    /// @brief 从目录及子目录中检索出所有文件名
    /// @param dir 要查找的文件夹
    /// @param nameFilters 文件过滤
    /// @param subDir 是否包含子目录
    /// @return 找到的文件列表
    static QStringList searchFiles(const QString& dir, const QStringList& nameFilters, bool subDir=false);

    /// @brief 复制文件
    /// @param fromFile 源文件名
    /// @param toFile 目的文件名
    /// @param bufferSize 缓冲大小，默认是 defaultBufferSize
    /// @see defaultBufferSize
    /// @return 复制的数据大小
    static qint64 copy(const QString &fromFile, const QString &toFile,
                       qint64 bufferSize = defaultBufferSize);

    /// @brief 复制文件
    /// @param fromFile 源文件名
    /// @param toFile 目的文件名
    /// @param fromFileOffset 源文件相对于文件开始处的偏移量
    /// @param copySize 复制的大小，默认是 -1，复制到源文件结尾处
    /// @param bufferSize 缓冲大小，默认是 defaultBufferSize
    /// @see defaultBufferSize
    /// @return 复制的数据大小
    static qint64 copy(const QString &fromFile, const QString &toFile,
                       qint64 fromFileOffset, qint64 copySize = -1,
                       qint64 bufferSize = defaultBufferSize);

    /// @brief 从源文件追加复制到目的文件结尾处
    /// @param fromFile 源文件名
    /// @param toFile 目的文件名
    /// @param bufferSize 缓冲大小，默认是 defaultBufferSize
    /// @see defaultBufferSize
    /// @return 追加复制的数据大小
    static qint64 append(const QString &fromFile, const QString &toFile,
                         qint64 bufferSize = defaultBufferSize);

    /// @brief 从源文件追加复制到目的文件结尾处
    /// @param fromFile 源文件名
    /// @param toFile 目的文件名
    /// @param fromFileOffset 源文件相对于文件开始处的偏移量
    /// @param appendSize 追加复制的大小，默认是 -1，复制到源文件结尾处
    /// @param bufferSize 缓冲大小，默认是 defaultBufferSize
    /// @see defaultBufferSize
    /// @return 追加复制的数据大小
    static qint64 append(const QString &fromFile, const QString &toFile,
                         qint64 fromFileOffset, qint64 appendSize = -1,
                         qint64 bufferSize = defaultBufferSize);

    /// @brief 按字节分解文件
    /// @param fromFile 源文件名
    /// @param toDir 目的文件夹
    /// @param splitSize 分解后单个文件大小
    /// @param bufferSize 缓冲大小，默认是 defaultBufferSize
    /// @see defaultBufferSize
    /// @return 分解后的文件个数
    /// @par 示例:
    /// @code
    /// 如果源文件是 d:\123.iso，目的文件夹是d:\11，
    /// 分解后的文件名是123.iso.1,123.iso.2,...这种形式
    /// @endcode
    static int split(const QString &fromFile, const QString &toDir,
                        qint64 splitSize, qint64 bufferSize = defaultBufferSize);

    /// @brief 按字节合并文件
    /// @param fromFileList 源文件列表
    /// @param toFile 目的文件名
    /// @param bufferSize 缓冲大小，默认是 defaultBufferSize
    /// @see defaultBufferSize
    /// @return 合并的数据
    static qint64 join(const QStringList &fromFileList, const QString &toFile,
                        qint64 bufferSize = defaultBufferSize);

    /// @brief 生成指定字符填充的“大笨蛋”文档，常用于光盘映像
    /// @param fileName 生成的文件名
    /// @param fileSize 文件大小
    /// @param fill 填充字符，默认 0x00
    /// @param bufferSize 缓冲大小，默认是 defaultBufferSize
    /// @see defaultBufferSize
    /// @return 生成的数据大小
    static qint64 makeDummyFile(const QString &fileName, qint64 fileSize,
                                const char fill = 0x00,
                                qint64 bufferSize = defaultBufferSize);

    /// @brief 复制目录树下所有的文件到新文件夹
    /// @param fromPath 源文件夹
    /// @param toPath 目的文件夹
    /// @param nameFilters 文件过滤
    /// @param overWrite 是否覆盖
    /// @return 复制的文件数量
    int copyDir(const QString& fromPath, const QString& toPath, const QStringList &nameFilters = QStringList(),
                bool overWrite = true);

    /// @brief 复制文件列表到新文件夹
    /// @param files 源文件列表
    /// @param toPath 目的文件夹
    /// @param overWrite 是否覆盖
    /// @return 复制的文件数量
    int copyFiles(const QStringList &files, const QString &toPath, bool overWrite = true);

    /// @brief 重置m_copyFileCount为0
    void resetCopyFileCount();

Q_SIGNALS:
    /// @brief 信号：当前复制的文件的计数和文件名
    /// @param count 第几个文件
    /// @param name 源文件名
    void currentFile(int count, const QString &name);

private:
    int m_copyFileCount;

    void doDirTree(const QString& fromPath, const QString &toPath, const QStringList &nameFilters, bool overWrite,
                   QStringList& findFiles, bool isFind);
    QString formatPath(const QString &path);

private:
    // 提取源文件数据到目的文件
    static qint64 dump(const QString &fromFile, const QString &toFile, QIODevice::OpenMode fromOpenMode,
                       QIODevice::OpenMode toOpenMode, qint64 fromFileOffset, qint64 toFileOffset, qint64 dumpSize,
                       qint64 bufferSize);

    // 写入数据
    static qint64 write(QIODevice &from, QIODevice &to, qint64 writeSize, qint64 bufferSize);
};

#endif // TIANCHI_TCIO_H
