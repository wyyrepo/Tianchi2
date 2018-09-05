#include "tcWndSizer.h"
#include <QMainWindow>
#include <QMouseEvent>
#include <QDebug>

TcWndSizer::TcWndSizer(QWidget* parent)
    : QObject(parent)
    , m_borderWidth(8)
{
    m_widget = parent;
    m_widgetCursor = parent->cursor();
    QMainWindow* mw = qobject_cast<QMainWindow*>(m_widget);
    if ( mw != nullptr )
    {
        mw->centralWidget()->setMouseTracking(this);
    }
    m_widget->setMouseTracking(true);
    m_widget->installEventFilter(this);	// 代理窗体事件
}

void TcWndSizer::setBorderWidth(int width)
{
    m_borderWidth = width;
}

bool TcWndSizer::eventFilter(QObject* target, QEvent* event)
{
    static QPoint   pressedPos;
    static int      sizeDirection = 0;

    QMouseEvent* mouseEvent;
    switch((unsigned long)(event->type()))
    {
    case QEvent::MouseButtonPress:
        if ( sizeDirection != 0 )
        {
            mouseEvent = (QMouseEvent*) event;
            pressedPos = mouseEvent->globalPos();
            return true;
        }
        break;
    case QEvent::MouseButtonRelease:
        if ( sizeDirection != 0 )
        {
            sizeDirection = 0;
            return true;
        }
        break;
    case QEvent::MouseMove:
        mouseEvent = (QMouseEvent*) event;
        if ( mouseEvent->buttons() == Qt::NoButton )
        {
            if ( mouseEvent->pos().x() < m_borderWidth && mouseEvent->pos().y() < m_borderWidth ) // 左上
            {
                m_widget->setCursor(Qt::SizeFDiagCursor);
                sizeDirection = 5;
            }else
            if ( mouseEvent->pos().x() > (m_widget->width() - m_borderWidth) && mouseEvent->pos().y() > (m_widget->height() - m_borderWidth) ) // 右下
            {
                m_widget->setCursor(Qt::SizeFDiagCursor);
                sizeDirection = 10;
            }else
            if ( mouseEvent->pos().x() < m_borderWidth && mouseEvent->pos().y() > (m_widget->height() - m_borderWidth) ) // 左下
            {
                m_widget->setCursor(Qt::SizeBDiagCursor);
                sizeDirection = 6;
            }else
            if ( mouseEvent->pos().x() > (m_widget->width() - m_borderWidth) && mouseEvent->pos().y() < m_borderWidth ) // 右上
            {
                m_widget->setCursor(Qt::SizeBDiagCursor);
                sizeDirection = 9;
            }else
            if ( mouseEvent->pos().y() < m_borderWidth ) // 上
            {
                m_widget->setCursor(Qt::SizeVerCursor);
                sizeDirection = 1;
            }else
            if ( mouseEvent->pos().y() > (m_widget->height() - m_borderWidth) ) // 下
            {
                m_widget->setCursor(Qt::SizeVerCursor);
                sizeDirection = 2;
            }else
            if ( mouseEvent->pos().x() < m_borderWidth ) // 左
            {
                m_widget->setCursor(Qt::SizeHorCursor);
                sizeDirection = 4;
            }else
            if ( mouseEvent->pos().x() > (m_widget->width() - m_borderWidth) ) // 右
            {
                m_widget->setCursor(Qt::SizeHorCursor);
                sizeDirection = 8;
            }else
            {
                m_widget->setCursor(m_widgetCursor);
                sizeDirection = 0;
            }
        }
        if ( mouseEvent->buttons() & Qt::LeftButton )
        {
            QRect rt = m_widget->geometry();
            switch(sizeDirection)
            {
            case 1: // 上
                rt.setY(rt.y() + mouseEvent->globalPos().y() - pressedPos.y());
                break;
            case 2: // 下
                rt.setBottom(rt.bottom() + mouseEvent->globalPos().y() - pressedPos.y());
                break;
            case 4: // 左
                rt.setX(rt.x() + mouseEvent->globalPos().x() - pressedPos.x());
                break;
            case 8: // 右
                rt.setRight(rt.right() + mouseEvent->globalPos().x() - pressedPos.x());
                break;
            case 5: // 左上
                rt.setX(rt.x() + mouseEvent->globalPos().x() - pressedPos.x());
                rt.setY(rt.y() + mouseEvent->globalPos().y() - pressedPos.y());
                break;
            case 6: // 左下
                rt.setX(rt.x() + mouseEvent->globalPos().x() - pressedPos.x());
                rt.setBottom(rt.bottom() + mouseEvent->globalPos().y() - pressedPos.y());
                break;
            case 9: // 右上
                rt.setRight(rt.right() + mouseEvent->globalPos().x() - pressedPos.x());
                rt.setY(rt.y() + mouseEvent->globalPos().y() - pressedPos.y());
                break;
            case 10: // 右下
                rt.setRight(rt.right() + mouseEvent->globalPos().x() - pressedPos.x());
                rt.setBottom(rt.bottom() + mouseEvent->globalPos().y() - pressedPos.y());
                break;
            }
            if ( rt.width() >= m_widget->minimumWidth() && rt.width() <= m_widget->maximumWidth()
              && rt.height() >= m_widget->minimumHeight() && rt.height() <= m_widget->maximumHeight() )
            {
                m_widget->setGeometry(rt);
                pressedPos = mouseEvent->globalPos();
            }
        }
        break;
    }
    return QObject::eventFilter(target, event);
}
