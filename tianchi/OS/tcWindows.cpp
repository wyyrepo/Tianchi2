#include <QtCore>
#if defined(Q_OS_WIN)

#include "tcWindows.h"

#include <QSettings>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QWidget>
#include <QPainter>

#include <qt_windows.h>
#include <windowsx.h>

#ifndef PIDLIST_ABSOLUTE
typedef ITEMIDLIST *PIDLIST_ABSOLUTE;
#endif

void TcWindows::autoStart(const QString& name, const QString& program)
{
    const QString HKEY_DIRECTORY = "Software/Microsoft/Windows/CurrentVersion/Run/";
    QSettings reg("HKEY_CURRENT_USER", QSettings::NativeFormat);
    if ( ! program.isEmpty() )
    {
        reg.setValue(HKEY_DIRECTORY + name, program);
    }else
    {
        reg.remove(HKEY_DIRECTORY + name);
    }
}

QString TcWindows::getWinSysDir(int pathid)
{
    CoInitialize(NULL);
    PIDLIST_ABSOLUTE pidl;  // Force start menu cache update
    wchar_t MyDir[_MAX_PATH] = {0};
    if (SUCCEEDED(SHGetFolderLocation(0, pathid, 0, 0, &pidl)))
    {
        SHGetPathFromIDList(pidl,MyDir);
        SHChangeNotify(SHCNE_UPDATEDIR, SHCNF_IDLIST, pidl, 0);
        CoTaskMemFree(pidl);
    }
    CoUninitialize();
    return QString::fromWCharArray(MyDir).replace("\\","/");
}

bool TcWindows::createLink(const QString &fileName, const QString &linkName,
                const QString &arguments, const QString &iconPath,
                const QString &iconId)
{
    QString tlinkName = linkName;
    if (!tlinkName.endsWith(".lnk")) tlinkName += ".lnk";
    bool success = QFile::link(fileName, tlinkName);

    if (!success)
        return success;

    CoInitialize(NULL);

    QString workingDir = QFileInfo(fileName).absolutePath();
    workingDir = QDir::toNativeSeparators(workingDir);

    IShellLink *psl = NULL;
    if (FAILED(CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (LPVOID*)&psl)))
    {
        CoUninitialize();
        return success;
    }

    psl->SetPath((wchar_t *)QDir::toNativeSeparators(fileName).utf16());
    psl->SetWorkingDirectory((wchar_t *)workingDir.utf16());
    if (!arguments.isNull())
        psl->SetArguments((wchar_t*)arguments.utf16());
    if (!iconPath.isNull())
        psl->SetIconLocation((wchar_t*)(iconPath.utf16()), iconId.toInt());

    IPersistFile *ppf = NULL;
    if (SUCCEEDED(psl->QueryInterface(IID_IPersistFile, (void **)&ppf))) {
        ppf->Save((wchar_t*)QDir::toNativeSeparators(tlinkName).utf16(), true);
        ppf->Release();
    }
    psl->Release();

    PIDLIST_ABSOLUTE pidl;

    if (SUCCEEDED(SHGetFolderLocation(0, CSIDL_STARTMENU, 0, 0, &pidl))) {
        SHChangeNotify(SHCNE_UPDATEDIR, SHCNF_IDLIST, pidl, 0);
        CoTaskMemFree(pidl);
    }
    if (SUCCEEDED(SHGetFolderLocation(0, CSIDL_COMMON_STARTMENU, 0, 0, &pidl))) {
        SHChangeNotify(SHCNE_UPDATEDIR, SHCNF_IDLIST, pidl, 0);
        CoTaskMemFree(pidl);
    }
    CoUninitialize();
    return success;
}

bool TcWindows::resizeEvent(const QByteArray&, void* msg, long* result, const QRect& wndRect)
{
    bool ret = false;
    MSG* message = (MSG*) msg;
    switch(message->message)
    {
    case WM_NCHITTEST:
        int xPos = GET_X_LPARAM(message->lParam) - wndRect.x();
        int yPos = GET_Y_LPARAM(message->lParam) - wndRect.y();
//        if ( childAt(xPos, yPos) == nullptr )
//        {
//            // 移动
//            *result = HTCAPTION;
//        }else
//        {
//            return false;
//        }
        ret = true;
        if ( abs(xPos) <= 5 && abs(yPos) <= 5 )
        {
            *result = HTTOPLEFT;
        }else
        if ( abs(xPos-wndRect.width()) <= 5 && abs(yPos) <= 5 )
        {
            *result = HTTOPRIGHT;
        }else
        if ( abs(xPos) <= 5 && abs(yPos-wndRect.height()) <= 5 )
        {
            *result = HTBOTTOMLEFT;
        }else
        if ( abs(xPos-wndRect.width()) <= 5 && abs(yPos-wndRect.height()) <= 5 )
        {
            *result = HTBOTTOMRIGHT;
        }else
        if ( abs(xPos) <= 3 )
        {
            *result = HTLEFT;
        }else
        if ( abs(xPos-wndRect.width()) <= 3 )
        {
            *result = HTRIGHT;
        }else
        if ( abs(yPos) <= 3 )
        {
            *result = HTTOP;
        }else
        if ( abs(yPos-wndRect.height()) <= 3 )
        {
            *result = HTBOTTOM;
        }else
        {
            ret = false;
        }
    }
    return ret;
}

QString TcWindows::userName()
{
    DWORD dwSize = 0;
    ::GetUserNameA(NULL, &dwSize);
    char *szBuf = new char[dwSize+1];
    szBuf[0] = '\0';
    ::GetUserNameA(szBuf, &dwSize);
    QString ret = szBuf;
    delete [] szBuf;

    return ret;
}

#endif // Q_OS_WIN

