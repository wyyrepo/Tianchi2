#include <QtCore>
#if defined(Q_OS_WIN)

#include "tcIO.h"

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QDataStream>
#include <QQueue>

//这里的代码是有效的
#include <qt_windows.h>
#endif

TcIO::TcIO(QObject* parent)
    : QObject(parent)
    , m_copyFileCount(0)
{
}

bool TcIO::loadFromFile(QString &context, const QString &filename,
        const QString &codec /* = QString() */)
{
    bool ret = false;
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly))
    {
       QTextStream in(&file);
       if (!codec.isEmpty())
       {
           in.setCodec(codec.toLatin1().data());
       }
       context = in.readAll();
       ret = true;
       file.close();
    }
    return ret;
}

bool TcIO::readFileContent(QByteArray& context, const QString& filename)
{
    bool ret = false;
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly))
    {
       context = file.readAll();
       ret = true;
       file.close();
    }
    return ret;
}

QString TcIO::uniqueFileName(const QString &dir,
        const QString &fileTemplate,
        const QString &suffix /* = QString() */)
{
    QString fileDir    = dir;
    QString filePrefix = fileTemplate;
    QString fileSuffix = suffix;

    QFileInfo f;
    if (fileDir.isEmpty())
    {
        f.setFile(fileTemplate);
        fileDir    = f.absoluteDir().absolutePath();
        fileSuffix = f.suffix();
        if (!fileSuffix.isEmpty())
        {
            filePrefix = filePrefix.mid(0,
                    filePrefix.length() - fileSuffix.length() - 1);
        }
    }
    if (fileSuffix.isEmpty())
    {
        f.setFile(fileTemplate);
        fileSuffix = f.suffix();
        if (!fileSuffix.isEmpty())
        {
            filePrefix = filePrefix.mid(0,
                    filePrefix.length() - fileSuffix.length() - 1);
        }
    }
    QString ret = fileDir + QDir::separator() + filePrefix + "." + fileSuffix;
    f.setFile(ret);
    int index = 2;
    while (f.exists())
    {
        ret = fileDir + QDir::separator() + filePrefix
            + "(" + QString::number(index++) + ")." + fileSuffix;
        f.setFile(ret);
    }
    return ret;
}

QString TcIO::fileVersion(const QString& exeFile)
{
    QString ret;

#if defined(Q_OS_WIN)
    int size = GetFileVersionInfoSize(exeFile.toStdWString().c_str(), NULL);
    if (size > 0)
    {
        char* data = new char[size +1];
        if (GetFileVersionInfo(exeFile.toStdWString().c_str(), 0, size, data))
        {
            VS_FIXEDFILEINFO* fileInfo;
            unsigned int      fileInfoSize = 0;
            if (VerQueryValue(data, L"\\", (void**)&fileInfo, &fileInfoSize))
            {
                int vMajor  = HIWORD(fileInfo->dwFileVersionMS);
                int vMinor  = LOWORD(fileInfo->dwFileVersionMS);
                int Release = HIWORD(fileInfo->dwFileVersionLS);
                int vBuild  = LOWORD(fileInfo->dwFileVersionLS);
                ret.append(QString::number(vMajor)).append(".")
                        .append(QString::number(vMinor)).append(".")
                        .append(QString::number(Release)).append(".")
                        .append(QString::number(vBuild));
            }
        }
        delete [] data;
    }
#else
    Q_UNUSED(exeFile)
#endif
    return ret;
}

QString TcIO::fileVersion(const QString& exeFile, int& vMajor, int& vMinor, int& Release, int& vBuild)
{
    QString ret;

    vMajor = vMinor = Release = vBuild = 0;

#if defined(Q_OS_WIN)
    int size = GetFileVersionInfoSize(exeFile.toStdWString().c_str(), NULL);
    if (size > 0)
    {
        char* data = new char[size +1];
        if (GetFileVersionInfo(exeFile.toStdWString().c_str(), 0, size, data))
        {
            VS_FIXEDFILEINFO* fileInfo;
            unsigned int      fileInfoSize = 0;
            if (VerQueryValue(data, L"\\", (void**)&fileInfo, &fileInfoSize))
            {
                vMajor  = HIWORD(fileInfo->dwFileVersionMS);
                vMinor  = LOWORD(fileInfo->dwFileVersionMS);
                Release = HIWORD(fileInfo->dwFileVersionLS);
                vBuild  = LOWORD(fileInfo->dwFileVersionLS);
                ret.append(QString::number(vMajor)).append(".")
                        .append(QString::number(vMinor)).append(".")
                        .append(QString::number(Release)).append(".")
                        .append(QString::number(vBuild));
            }
        }
        delete [] data;
    }
#else
    Q_UNUSED(exeFile)
#endif
    return ret;
}

QStringList TcIO::searchFiles(const QString& path, const QStringList& nameFilters, bool subDir)
{
    QStringList ret;
    // 这个函数可以执行任何任务，
    // 这里只是简单地输出各个文件（夹）的名字
    QDir dir(path);
    QStringList
    list = dir.entryList(QDir::Dirs, QDir::Name);
    for( QStringList::Iterator it = list.begin(); it != list.end(); it++ )
    {
        if ( "." != *it && ".." != *it )
        {
            QString dirName = path + QDir::separator() + *it;
            if ( subDir )
            {
                searchFiles(dirName, nameFilters, subDir);
            }
        }
    }
    list = dir.entryList(nameFilters, QDir::Files, QDir::Name);
    for (QStringList::Iterator it = list.begin(); it != list.end(); it++)
    {
        ret.append(*it);
    }
    return ret;
}

//const int TcIO::KB = 1024; // KB 1024
//const int TcIO::MB = 1048576; // MB 1024*1024
//const int TcIO::GB = 1073741824; // GB 1024*1024*1024
//const int TcIO::defaultBufferSize = 4 * TcIO::MB; // 4MB 4*1024*1024

qint64 TcIO::copy(const QString &fromFile,
        const QString &toFile,
        qint64 bufferSize)
{
    return dump(fromFile, toFile, QIODevice::ReadOnly, QIODevice::WriteOnly,
            0, 0, -1, bufferSize);
}

qint64 TcIO::copy(const QString &fromFile,
        const QString &toFile,
        qint64 fromFileOffset,
        qint64 copySize,
        qint64 bufferSize)
{
    return dump(fromFile, toFile, QIODevice::ReadOnly, QIODevice::WriteOnly,
            fromFileOffset, 0, copySize, bufferSize);
}

qint64 TcIO::append(const QString &fromFile,
        const QString &toFile,
        qint64 bufferSize)
{
    return dump(fromFile, toFile, QIODevice::ReadOnly, QIODevice::Append,
            0, 0, -1, bufferSize);
}

qint64 TcIO::append(const QString &fromFile,
        const QString &toFile,
        qint64 fromFileOffset,
        qint64 appendSize,
        qint64 bufferSize)
{
    return dump(fromFile, toFile, QIODevice::ReadOnly, QIODevice::Append,
            fromFileOffset, 0, appendSize , bufferSize);
}

int TcIO::split(const QString &fromFile,
        const QString &toDir,
        qint64 splitSize,
        qint64 bufferSize)
{
    QDir to_dir(toDir);

    if (!to_dir.exists())
    {
        to_dir.mkpath(toDir);
    }

    int file_count = 0;
    QFile from_file(fromFile);
    qint64 from_size = from_file.size();
    QString to_file;
    QString from_file_name(QFileInfo(fromFile).fileName());
    qint64 write_size;

    while (from_size > 0)
    {
        write_size = from_size > splitSize ? splitSize : from_size;
        to_file = QString("%1/%2.%3").arg(toDir)
            .arg(from_file_name).arg(file_count + 1);
        dump(fromFile, to_file, QIODevice::ReadOnly, QIODevice::WriteOnly,
                splitSize * file_count, 0, write_size, bufferSize);
        from_size -= write_size;
        file_count++;
    }

    return file_count;
}

qint64 TcIO::join(const QStringList &fromFileList,
        const QString &toFile,
        qint64 bufferSize)
{
    int size = fromFileList.size();
    qint64 file_size = 0;
    qint64 dump_size = 0;

    for (int i = 0; i < size; i++)
    {
        dump_size = dump(fromFileList[i], toFile, QIODevice::ReadOnly,
                QIODevice::Append, 0, 0, -1, bufferSize);
        file_size += dump_size != -1 ? dump_size : 0;
    }

    return file_size;
}

qint64 TcIO::makeDummyFile(const QString &fileName,
        qint64 fileSize,
        const char fill,
        qint64 bufferSize)
{
    QFile file(fileName);
    QByteArray data(bufferSize, fill);
    qint64 write_size = bufferSize;
    qint64 sum_write_size = 0;

    try
    {
        file.open(QIODevice::WriteOnly);

        while (fileSize > 0)
        {
            write_size = fileSize < bufferSize ? fileSize: bufferSize;
            write_size = file.write(data.data(), write_size);
            fileSize -= write_size;
            sum_write_size += write_size;
        }
    }
    catch (...)
    {
        file.close();
        return -1;
    }

    file.close();
    return sum_write_size;
}

qint64 TcIO::dump(const QString &fromFile,
        const QString &toFile,
        QIODevice::OpenMode fromOpenMode,
        QIODevice::OpenMode toOpenMode,
        qint64 fromFileOffset,
        qint64 toFileOffset,
        qint64 dumpSize,
        qint64 bufferSize)
{
    QFile from(fromFile);
    QFile to(toFile);
    qint64 sum_read_size = 0;

    try
    {
        from.open(fromOpenMode);
        to.open(toOpenMode);
        from.seek(fromFileOffset);

        if (toOpenMode != QIODevice::Append)
        {
            to.seek(toFileOffset);
        }

        sum_read_size = write(from, to, dumpSize, bufferSize);
    }
    catch (...)
    {
        from.close();
        to.close();
        return -1;
    }

    from.close();
    to.close();
    return sum_read_size;
}

qint64 TcIO::write(QIODevice &from,
        QIODevice &to,
        qint64 writeSize,
        qint64 bufferSize)
{
    QByteArray data(bufferSize, 0x00);
    qint64 read_size = 0;
    qint64 ready_read_size = bufferSize;
    qint64 sum_read_size = 0;

    while (!from.atEnd())
    {
        if (writeSize > -1)
        {
            ready_read_size = writeSize < bufferSize ? writeSize: bufferSize;
            writeSize -= ready_read_size;
        }

        read_size = from.read(data.data(), ready_read_size);
        to.write(data.data(), read_size);
        sum_read_size += read_size;

        if (writeSize == 0)
        {
            break;
        }
    }

    return sum_read_size;
}

int TcIO::copyDir(const QString &fromPath, const QString &toPath, const QStringList &nameFilters, bool overWrite)
{
    resetCopyFileCount();

    if ((!fromPath.isEmpty()) && (QFileInfo(fromPath).exists()))
    {
        QStringList files;
        doDirTree(fromPath, toPath, nameFilters, overWrite, files, false);
    }
    return m_copyFileCount;
}

int TcIO::copyFiles(const QStringList &files, const QString &toPath, bool overWrite)
{
    int size = files.size();
    int count = 0;
    QString to_path(formatPath(toPath));
    QDir to_dir;
    QFile old_file;
    QFile new_file;
    QFileInfo old_file_info;
    QFileInfo new_file_info;

    for (int i = 0; i < size; i++)
    {
        old_file.setFileName(files[i]);
        old_file_info.setFile(old_file);
        new_file.setFileName(to_path + QDir::separator()
                + old_file_info.fileName());
        new_file_info.setFile(new_file);
        to_dir.setPath(new_file.fileName());
        to_dir.mkpath(new_file_info.path());

        if ((overWrite) || (!new_file.exists()))
        {
            old_file.copy(new_file.fileName());
            m_copyFileCount++;
            count++;
            Q_EMIT currentFile(m_copyFileCount, files[i]);
        }
    }
    return count;
}

void TcIO::resetCopyFileCount()
{
    m_copyFileCount = 0;
}

void TcIO::doDirTree(const QString &fromPath, const QString &toPath, const QStringList &nameFilters, bool overWrite,
                     QStringList &findFiles, bool isFind)
{
    QQueue<QString> from_all_dirs;
    QQueue<QString> to_all_dirs;
    QDir find_in_dir;
    QStringList file_list;
    QStringList dir_list;
    QString current_from_path;
    QString current_to_path;

    from_all_dirs.push_back(fromPath);
    to_all_dirs.push_back(toPath);

    while (from_all_dirs.size() > 0)
    {
        current_from_path = from_all_dirs.head();
        current_to_path = to_all_dirs.head();
        find_in_dir.setPath(current_from_path);
        file_list = find_in_dir.entryList(nameFilters, QDir::Files);

        for (int i = 0; i < file_list.size(); i++)
        {
            file_list[i] = formatPath(current_from_path) + file_list[i];
        }

        if (isFind)
        {
            findFiles += file_list;
        }
        else
        {
            copyFiles(file_list, current_to_path, overWrite);
        }
        dir_list = find_in_dir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot);

        for (int i = 0; i < dir_list.size(); i++)
        {
            from_all_dirs += formatPath(current_from_path) + dir_list[i];
            to_all_dirs += formatPath(current_to_path) + dir_list[i];
        }
        from_all_dirs.pop_front();
        to_all_dirs.pop_front();
    }
}

QString TcIO::formatPath(const QString &path)
{
    QString new_path = path;
    QString last_char = path[path.size() - 1];

    if (last_char != "\\" && last_char != "/")
    {
        new_path += QDir::separator();
    }
    return new_path;
}
