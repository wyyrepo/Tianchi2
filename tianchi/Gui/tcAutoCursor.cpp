#include "tcAutoCursor.h"

/*
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
  #include <QGuiApplication>
#else
  #include <QApplication>
#endif

// *********************************************************************************************************************
TcAutoCursor::TcAutoCursor(Qt::CursorShape shape)
{
  #if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
    QGuiApplication::setOverrideCursor(QCursor(shape));
  #else
    QApplication::setOverrideCursor(QCursor(shape));
  #endif
}

TcAutoCursor::~TcAutoCursor()
{
    restore();
}

void TcAutoCursor::restore()
{
  #if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
    QGuiApplication::restoreOverrideCursor();
  #else
    QApplication::restoreOverrideCursor();
  #endif
}

// *********************************************************************************************************************
TcCursorWait::TcCursorWait()
    : TcAutoCursor(Qt::WaitCursor)
{

}

// *********************************************************************************************************************
TcCursorBusy::TcCursorBusy()
    : TcAutoCursor(Qt::BusyCursor)
{

}
*/
