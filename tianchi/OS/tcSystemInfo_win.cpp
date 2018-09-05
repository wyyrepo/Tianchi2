#include "tcSystemInfo.h"

#ifdef Q_CC_MINGW
# ifndef _WIN32_WINNT
#  define _WIN32_WINNT 0x0501
# endif
#endif

#include <psapi.h>
#include <tlhelp32.h>
#include <winbase.h>
#include <winnetwk.h>
#include <Strsafe.h>

#ifndef Q_CC_MINGW
#pragma comment(lib, "mpr.lib")
#endif

#include <QList>
#include <QDir>
#include <QLibrary>

// *********************************************************************************************************************
// Link & TcRunInfo
// *********************************************************************************************************************
#ifdef Q_OS_WIN
class Link
{
public:
    explicit Link(const QString &path);
    static Link create(const QString &link, const QString &targetPath);
    QString targetPath() const;
    bool targetExists();
    bool exists();
    bool isValid();
    bool remove();

private:
    QString m_path;
};

#if !defined(REPARSE_DATA_BUFFER_HEADER_SIZE)

typedef struct _REPARSE_DATA_BUFFER {
    ULONG  ReparseTag;
    USHORT ReparseDataLength;
    USHORT Reserved;
    union {
        struct {
            USHORT SubstituteNameOffset;
            USHORT SubstituteNameLength;
            USHORT PrintNameOffset;
            USHORT PrintNameLength;
            ULONG  Flags;
            WCHAR  PathBuffer[1];
        } SymbolicLinkReparseBuffer;
        struct {
            USHORT SubstituteNameOffset;
            USHORT SubstituteNameLength;
            USHORT PrintNameOffset;
            USHORT PrintNameLength;
            WCHAR  PathBuffer[1];
        } MountPointReparseBuffer;
        struct {
            UCHAR DataBuffer[1];
        } GenericReparseBuffer;
    };
} REPARSE_DATA_BUFFER, *PREPARSE_DATA_BUFFER;
#define REPARSE_DATA_BUFFER_HEADER_SIZE FIELD_OFFSET(REPARSE_DATA_BUFFER, GenericReparseBuffer)

#endif

class FileHandleWrapper
{
public:
    FileHandleWrapper(const QString &path)
        : m_dirHandle(INVALID_HANDLE_VALUE)
    {
        QString normalizedPath = QString(path).replace(QLatin1Char('/'), QLatin1Char('\\'));
        m_dirHandle = CreateFile((wchar_t*)normalizedPath.utf16(), GENERIC_READ | GENERIC_WRITE, 0, 0,
            OPEN_EXISTING, FILE_FLAG_OPEN_REPARSE_POINT | FILE_FLAG_BACKUP_SEMANTICS, 0);

        if (m_dirHandle == INVALID_HANDLE_VALUE) {
            qWarning() << QString::fromLatin1("Could not open: '%1'; error: %2\n").arg(path).arg(GetLastError());
        }
    }

    ~FileHandleWrapper() {
        if (m_dirHandle != INVALID_HANDLE_VALUE)
            CloseHandle(m_dirHandle);
    }

    HANDLE handle() {
        return m_dirHandle;
    }

private:
    HANDLE m_dirHandle;
};

QString readWindowsSymLink(const QString &path)
{
    QString result;
    FileHandleWrapper dirHandle(path);
    if (dirHandle.handle() != INVALID_HANDLE_VALUE) {
        REPARSE_DATA_BUFFER* reparseStructData = (REPARSE_DATA_BUFFER*)calloc(1, MAXIMUM_REPARSE_DATA_BUFFER_SIZE);
        DWORD bytesReturned = 0;
        if (::DeviceIoControl(dirHandle.handle(), FSCTL_GET_REPARSE_POINT, 0, 0, reparseStructData,
            MAXIMUM_REPARSE_DATA_BUFFER_SIZE, &bytesReturned, 0)) {
                if (reparseStructData->ReparseTag == IO_REPARSE_TAG_MOUNT_POINT) {
                    int length = reparseStructData->MountPointReparseBuffer.SubstituteNameLength / sizeof(wchar_t);
                    int offset = reparseStructData->MountPointReparseBuffer.SubstituteNameOffset / sizeof(wchar_t);
                    const wchar_t* PathBuffer = &reparseStructData->MountPointReparseBuffer.PathBuffer[offset];
                    result = QString::fromWCharArray(PathBuffer, length);
                } else if (reparseStructData->ReparseTag == IO_REPARSE_TAG_SYMLINK) {
                    int length = reparseStructData->SymbolicLinkReparseBuffer.SubstituteNameLength / sizeof(wchar_t);
                    int offset = reparseStructData->SymbolicLinkReparseBuffer.SubstituteNameOffset / sizeof(wchar_t);
                    const wchar_t* PathBuffer = &reparseStructData->SymbolicLinkReparseBuffer.PathBuffer[offset];
                    result = QString::fromWCharArray(PathBuffer, length);
                }
                // cut-off "//?/" and "/??/"
                if (result.size() > 4 && result.at(0) == QLatin1Char('\\') && result.at(2) == QLatin1Char('?') && result.at(3) == QLatin1Char('\\'))
                    result = result.mid(4);
        }
        free(reparseStructData);
    }
    return result;
}

Link createJunction(const QString &linkPath, const QString &targetPath)
{
    if (!QDir().mkpath(linkPath)) {
        qWarning() << QString::fromLatin1("Could not create the mount directory: %1").arg(
            linkPath);
        return Link(linkPath);
    }
    FileHandleWrapper dirHandle(linkPath);
    if (dirHandle.handle() == INVALID_HANDLE_VALUE) {
        qWarning() << QString::fromLatin1("Could not open: '%1'; error: %2\n").arg(linkPath).arg(
            GetLastError());
        return Link(linkPath);
    }

    const QString szDestDir = QString::fromLatin1("\\??\\").arg(targetPath).replace(QLatin1Char('/'),
        QLatin1Char('\\'));

    // Allocates a block of memory for an array of num elements(1) and initializes all its bits to zero.
    REPARSE_DATA_BUFFER* reparseStructData = (REPARSE_DATA_BUFFER*)calloc(1,
        MAXIMUM_REPARSE_DATA_BUFFER_SIZE);
    reparseStructData->Reserved = 0;
    reparseStructData->ReparseTag = IO_REPARSE_TAG_MOUNT_POINT;
    reparseStructData->MountPointReparseBuffer.PrintNameLength = 0;
    reparseStructData->MountPointReparseBuffer.SubstituteNameOffset = 0;
    reparseStructData->MountPointReparseBuffer.SubstituteNameLength = szDestDir.length();
    reparseStructData->MountPointReparseBuffer.PrintNameOffset = szDestDir.length() + sizeof(WCHAR);

    uint spaceAfterGeneralData = sizeof(USHORT) * 5 + sizeof(WCHAR); //should be 12
    reparseStructData->ReparseDataLength = szDestDir.length() + spaceAfterGeneralData;

#ifndef Q_CC_MINGW
    StringCchCopy(reparseStructData->MountPointReparseBuffer.PathBuffer, 1024, (wchar_t*)szDestDir.utf16());
#else
    wcsncpy(reparseStructData->MountPointReparseBuffer.PathBuffer, (wchar_t*)szDestDir.utf16(), 1024);
#endif

    DWORD bytesReturned;
    if (!::DeviceIoControl(dirHandle.handle(), FSCTL_SET_REPARSE_POINT, reparseStructData,
        reparseStructData->ReparseDataLength + REPARSE_DATA_BUFFER_HEADER_SIZE, 0, 0,
        &bytesReturned, 0)) {
            qWarning() << QString::fromLatin1("Could not set the reparse point: for '%1' to %2; error: %3"
                ).arg(linkPath, targetPath).arg(GetLastError());
    }
    return Link(linkPath);
}

bool removeJunction(const QString &path)
{
    // Allocates a block of memory for an array of num elements(1) and initializes all its bits to zero.
    REPARSE_DATA_BUFFER* reparseStructData = (REPARSE_DATA_BUFFER*)calloc(1,
        MAXIMUM_REPARSE_DATA_BUFFER_SIZE);

    reparseStructData->ReparseTag = IO_REPARSE_TAG_MOUNT_POINT;

    { // extra scope because we need to close the dirHandle before we can remove that directory
        FileHandleWrapper dirHandle(path);

        DWORD bytesReturned;
        if (!::DeviceIoControl(dirHandle.handle(), FSCTL_DELETE_REPARSE_POINT, reparseStructData,
            REPARSE_GUID_DATA_BUFFER_HEADER_SIZE, 0, 0,
            &bytesReturned, 0)) {

            qWarning() << QString::fromLatin1("Could not remove the reparse point: '%1'; error: %3"
                ).arg(path).arg(GetLastError());
            return false;
        }
    }

    return QDir().rmdir(path);
}
#else
Link createLnSymlink(const QString &linkPath, const QString &targetPath)
{
    int linkedError = symlink(QFileInfo(targetPath).absoluteFilePath().toUtf8(),
        QFileInfo(linkPath).absoluteFilePath().toUtf8());
    if (linkedError != 0) {
        qWarning() << QString::fromLatin1("Could not create a symlink: from '%1' to %2; error: %3"
                    ).arg(linkPath, targetPath).arg(linkedError);
    }


    return Link(linkPath);
}

bool removeLnSymlink(const QString &path)
{
    return QFile::remove(path);
}

#endif

Link::Link(const QString &path) : m_path(path)
{
}

Link Link::create(const QString &link, const QString &targetPath)
{
    QStringList pathParts = QFileInfo(link).absoluteFilePath().split(QLatin1Char('/'));
    pathParts.removeLast();
    QString linkPath = pathParts.join(QLatin1String("/"));
    bool linkPathExists = QFileInfo(linkPath).exists();
    if (!linkPathExists)
        linkPathExists = QDir().mkpath(linkPath);
    if (!linkPathExists) {
        qWarning() << QString::fromLatin1("Could not create the needed directories: %1").arg(
            link);
        return Link(link);
    }

#ifdef Q_OS_WIN
    if (QFileInfo(targetPath).isDir())
        return createJunction(link, targetPath);

    qWarning() << QString::fromLatin1("At the moment the %1 can not create anything else as "\
        "junctions for directories under windows").arg(QLatin1String(Q_FUNC_INFO));
    return Link(link);
#else
    return createLnSymlink(link, targetPath);
#endif
}

QString Link::targetPath() const
{
#ifdef Q_OS_WIN
    return readWindowsSymLink(m_path);
#else
    return QFileInfo(m_path).readLink();
#endif
}

bool Link::exists()
{
#ifdef Q_OS_WIN
    return QFileInfo(m_path).exists();
#else
    return QFileInfo(m_path).isSymLink();
#endif
}

bool Link::targetExists()
{
    return QFileInfo(targetPath()).exists();
}

bool Link::isValid()
{
    return targetExists() && QFileInfo(m_path).exists();
}

bool Link::remove()
{
    if (!exists())
        return false;
#ifdef Q_OS_WIN
    return removeJunction(m_path);
#else
    return removeLnSymlink(m_path);
#endif
}

quint64 TcRunInfo::installedMemory()
{
    MEMORYSTATUSEX status;
    status.dwLength = sizeof(status);
    GlobalMemoryStatusEx(&status);
    return quint64(status.ullTotalPhys);
}

QList<TcVolumeInfo> TcRunInfo::mountedVolumes()
{
    // suppress message box shown while accessing possible unmounted devices
    const UINT old = SetErrorMode(SEM_FAILCRITICALERRORS);

    QList<TcVolumeInfo> tmp;
    TCHAR volumeGUID[MAX_PATH + 1] = { 0 };
    HANDLE handle = FindFirstVolume(volumeGUID, MAX_PATH);
    if (handle != INVALID_HANDLE_VALUE) {
        tmp += localVolumeInfosFromMountPoints(volumeGUID);
        while (FindNextVolume(handle, volumeGUID, MAX_PATH)) {
            tmp += localVolumeInfosFromMountPoints(volumeGUID);
        }
        FindVolumeClose(handle);
    }
    tmp += networkVolumeInfosFromMountPoints();

    QList<TcVolumeInfo> volumes;
    while (!tmp.isEmpty()) // update volume size information
        volumes.append(updateVolumeSizeInformation(tmp.takeFirst()));

    SetErrorMode(old);  // reset error mode
    return volumes;
}

struct EnumWindowsProcParam
{
    QList<TcProcessInfo> processes;
    QList<quint32> seenIDs;
};

const int KDSYSINFO_PROCESS_QUERY_LIMITED_INFORMATION = 0x1000;
typedef BOOL (WINAPI *QueryFullProcessImageNamePtr)(HANDLE, DWORD, char*, PDWORD);
typedef DWORD (WINAPI *GetProcessImageFileNamePtr)(HANDLE, char *, DWORD);
QList<TcProcessInfo> TcRunInfo::runningProcesses()
{
    EnumWindowsProcParam param;
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (!snapshot)
        return param.processes;

    QStringList deviceList;
    const DWORD bufferSize = 1024;
    char buffer[bufferSize + 1] = { 0 };
    if (QSysInfo::windowsVersion() <= QSysInfo::WV_5_2) {
        const DWORD size = GetLogicalDriveStringsA(bufferSize, buffer);
        deviceList = QString::fromLatin1(buffer, size).split(QLatin1Char(char(0)), QString::SkipEmptyParts);
    }

    QLibrary kernel32(QLatin1String("Kernel32.dll"));
    kernel32.load();
    QueryFullProcessImageNamePtr pQueryFullProcessImageNamePtr = (QueryFullProcessImageNamePtr) kernel32
        .resolve("QueryFullProcessImageNameA");

    QLibrary psapi(QLatin1String("Psapi.dll"));
    psapi.load();
    GetProcessImageFileNamePtr pGetProcessImageFileNamePtr = (GetProcessImageFileNamePtr) psapi
        .resolve("GetProcessImageFileNameA");

    PROCESSENTRY32 processStruct;
    processStruct.dwSize = sizeof(PROCESSENTRY32);
    bool foundProcess = Process32First(snapshot, &processStruct);
    while (foundProcess) {
        HANDLE procHandle = OpenProcess(QSysInfo::windowsVersion() > QSysInfo::WV_5_2
            ? KDSYSINFO_PROCESS_QUERY_LIMITED_INFORMATION : PROCESS_QUERY_INFORMATION, false, processStruct
                .th32ProcessID);

        bool succ = false;
        QString executablePath;
        DWORD bufferSize = 1024;

        if (QSysInfo::windowsVersion() > QSysInfo::WV_5_2) {
            succ = pQueryFullProcessImageNamePtr(procHandle, 0, buffer, &bufferSize);
            executablePath = QString::fromLatin1(buffer);
        } else if (pGetProcessImageFileNamePtr) {
            succ = pGetProcessImageFileNamePtr(procHandle, buffer, bufferSize);
            executablePath = QString::fromLatin1(buffer);
            for (int i = 0; i < deviceList.count(); ++i) {
                executablePath.replace(QString::fromLatin1( "\\Device\\HarddiskVolume%1\\" ).arg(i + 1),
                    deviceList.at(i));
            }
        }

        if (succ) {
            const quint32 pid = processStruct.th32ProcessID;
            param.seenIDs.append(pid);
            TcProcessInfo info;
            info.m_id = pid;
            info.m_name = executablePath;
            param.processes.append(info);
        }

        CloseHandle(procHandle);
        foundProcess = Process32Next(snapshot, &processStruct);

    }
    if (snapshot)
        CloseHandle(snapshot);

    kernel32.unload();
    return param.processes;
}

bool CALLBACK TerminateAppEnum(HWND hwnd, LPARAM lParam)
{
   DWORD dwID;
   GetWindowThreadProcessId(hwnd, &dwID);

   if (dwID == (DWORD)lParam)
      PostMessage(hwnd, WM_CLOSE, 0, 0);
   return true;
}

bool TcRunInfo::killProcess(const TcProcessInfo& process, int msecs)
{
    DWORD dwTimeout = msecs;
    if (msecs == -1)
        dwTimeout = INFINITE;

    // If we can't open the process with PROCESS_TERMINATE rights, then we give up immediately.
    HANDLE hProc = OpenProcess(SYNCHRONIZE | PROCESS_TERMINATE, false, process.id());
    if (hProc == 0)
        return false;

    // TerminateAppEnum() posts WM_CLOSE to all windows whose PID matches your process's.
    EnumWindows((WNDENUMPROC)TerminateAppEnum, (LPARAM)process.id());

    // Wait on the handle. If it signals, great. If it times out, then kill it.
    bool returnValue = false;
    if (WaitForSingleObject(hProc, dwTimeout) != WAIT_OBJECT_0)
        returnValue = TerminateProcess(hProc, 0);

    CloseHandle(hProc);
    return returnValue;
}

bool TcRunInfo::pathIsOnLocalDevice(const QString &path)
{
    if (!QFileInfo(path).exists())
        return false;

    if (path.startsWith(QLatin1String("\\\\")))
        return false;

    QDir dir(path);
    do {
        if (QFileInfo(dir, QString()).isSymLink()) {
            QString currentPath = QFileInfo(dir, QString()).absoluteFilePath();
            return pathIsOnLocalDevice(Link(currentPath).targetPath());
        }
    } while (dir.cdUp());

    const UINT DRIVE_REMOTE_TYPE = 4;
    if (path.contains(QLatin1Char(':'))) {
        const QLatin1Char nullTermination('\0');
        // for example "c:\"
        const QString driveSearchString = path.left(3) + nullTermination;
        WCHAR wCharDriveSearchArray[4];
        driveSearchString.toWCharArray(wCharDriveSearchArray);
        UINT type = GetDriveType(wCharDriveSearchArray);
        if (type == DRIVE_REMOTE_TYPE)
            return false;
    }

    return true;
}

TcVolumeInfo TcRunInfo::updateVolumeSizeInformation(const TcVolumeInfo &info)
{
    ULARGE_INTEGER bytesTotal;
    ULARGE_INTEGER freeBytesPerUser;

    TcVolumeInfo update = info;
    if (GetDiskFreeSpaceExA(qPrintable(info.volumeDescriptor()), &freeBytesPerUser, &bytesTotal, NULL)) {
        update.m_size = bytesTotal.QuadPart;
        update.m_availableSize = freeBytesPerUser.QuadPart;
    }
    return update;
}

/*!
    Returns a list of volume info objects that are mounted as network drive shares.
*/
QList<TcVolumeInfo> TcRunInfo::networkVolumeInfosFromMountPoints()
{
    QList<TcVolumeInfo> volumes;
    QFileInfoList drives = QDir::drives();
    foreach (const QFileInfo &drive, drives) {
        const QString driveLetter = QDir::toNativeSeparators(drive.canonicalPath());
        const uint driveType = GetDriveTypeA(qPrintable(driveLetter));
        switch (driveType) {
            case DRIVE_REMOTE: {
                char buffer[1024] = "";
                DWORD bufferLength = 1024;
                UNIVERSAL_NAME_INFOA *universalNameInfo = (UNIVERSAL_NAME_INFOA*) &buffer;
                if (WNetGetUniversalNameA(qPrintable(driveLetter), UNIVERSAL_NAME_INFO_LEVEL,
                    LPVOID(universalNameInfo), &bufferLength) == NO_ERROR) {
                        TcVolumeInfo info;
                        info.m_mountPath = driveLetter;
                        info.m_volumeDescriptor = QLatin1String(universalNameInfo->lpUniversalName);
                        volumes.append(info);
                }
            }   break;

            default:
                break;
        }
    }
    return volumes;
}

/*!
    Returns a list of volume info objects based on the given \a volumeGUID. The function also solves mounted
    volume folder paths. It does not return any network drive shares.
*/
QList<TcVolumeInfo> TcRunInfo::localVolumeInfosFromMountPoints(PTCHAR volumeGUID)
{
#ifndef UNICODE
#define fromWCharArray fromLatin1
#endif
    QList<TcVolumeInfo> volumes;
    DWORD bufferSize;
    TCHAR volumeNames[MAX_PATH + 1] = { 0 };
    if (GetVolumePathNamesForVolumeName(volumeGUID, volumeNames, MAX_PATH, &bufferSize)) {
        QStringList mountedPaths = QString::fromWCharArray(volumeNames, bufferSize).split(QLatin1Char(char(0)),
            QString::SkipEmptyParts);
        foreach (const QString &mountedPath, mountedPaths) {
            TcVolumeInfo info;
            info.m_mountPath = mountedPath;
            info.m_volumeDescriptor = QString::fromWCharArray(volumeGUID);
            volumes.append(info);
        }
    }
    return volumes;
#ifndef UNICODE
#undef fromWCharArray
#endif
}

