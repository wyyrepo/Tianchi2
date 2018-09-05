#include "tcScreenshot.h"
#include "ui_tcScreenshot.h"

#include <QPainter>
#include <QDebug>
#include <QDesktopWidget>
#include <QMouseEvent>
#include <QScreen>
#include <QDebug>

TcScreenshot::TcScreenshot()
    : QWidget(0, Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint)
    , ui(new Ui::TcScreenshot)
    , m_moveHole(0)
{
    ui->setupUi(this);

    //setAttribute(Qt::WA_DeleteOnClose); // 加上这句，此窗口在关闭后自动释放

    setAttribute(Qt::WA_TranslucentBackground);

    setMouseTracking(true);

    QPalette pal = palette();
    pal.setColor(QPalette::Background, Qt::transparent);
    setPalette(pal);
    setAutoFillBackground(true);

    setGeometry(QApplication::desktop()->screenGeometry());

    m_hole_rt = QRect(300, 200, 300, 400);
    makeRects();

    m_defaultCursor = cursor();
    setMouseTracking(true);
}

TcScreenshot::~TcScreenshot()
{
    delete ui;
}

void TcScreenshot::initSightRect(const QRect& rt)
{
    m_hole_rt = rt;
}

//QPixmap TcScreenshot::photograph()
//{
//    QScreen* screen = QGuiApplication::primaryScreen();
//    hide();
//    m_pixmap = screen->grabWindow(QApplication::desktop()->winId(), m_hole_rt.x(), m_hole_rt.y(), m_hole_rt.width(), m_hole_rt.height());
//    return pixmap();
//}

void TcScreenshot::makeRects()
{
    m_mask_rt1 = QRect(QPoint(0, 0), QPoint(QApplication::desktop()->screenGeometry().right(), m_hole_rt.top()));
    m_mask_rt2 = QRect(QPoint(0, m_hole_rt.top()+1), QPoint(m_hole_rt.left(), m_hole_rt.bottom()));
    m_mask_rt3 = QRect(QPoint(m_hole_rt.right(), m_hole_rt.top()+1),
                       QPoint(QApplication::desktop()->screenGeometry().right(), m_hole_rt.bottom()));
    m_mask_rt4 = QRect(QPoint(0, m_hole_rt.bottom()+1),
                       QPoint(QApplication::desktop()->screenGeometry().right(),
                              QApplication::desktop()->screenGeometry().bottom()));

    m_grip_1  = QRect(m_hole_rt.left() + m_hole_rt.width()/2-2, m_hole_rt.top()-2, 6, 6); // 上
    m_grip_2  = QRect(m_hole_rt.left() + m_hole_rt.width()/2-2, m_hole_rt.bottom()-2, 6, 6); // 下
    m_grip_4  = QRect(m_hole_rt.left() -2, m_hole_rt.top()+m_hole_rt.height()/2-2, 6, 6); // 左
    m_grip_8  = QRect(m_hole_rt.right()-2, m_hole_rt.top()+m_hole_rt.height()/2-2, 6, 6); // 右
    m_grip_5  = QRect(m_hole_rt.left() -2, m_hole_rt.top()   -2, 6, 6); // 左上
    m_grip_6  = QRect(m_hole_rt.left() -2, m_hole_rt.bottom()-2, 6, 6); // 左下
    m_grip_9  = QRect(m_hole_rt.right()-2, m_hole_rt.top   ()-2, 6, 6); // 右上
    m_grip_10 = QRect(m_hole_rt.right()-2, m_hole_rt.bottom()-2, 6, 6); // 右下

    sightRect(m_hole_rt);
}

void TcScreenshot::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    // QColor 最后一个参数表示背景透明度。
    painter.fillRect(m_hole_rt , QColor(0, 0,   0,  1));
    painter.fillRect(m_mask_rt1, QColor(0, 0, 255, 70));
    painter.fillRect(m_mask_rt2, QColor(0, 0, 255, 70));
    painter.fillRect(m_mask_rt3, QColor(0, 0, 255, 70));
    painter.fillRect(m_mask_rt4, QColor(0, 0, 255, 70));

    painter.fillRect(m_grip_1 , QColor(0, 0, 0));
    painter.fillRect(m_grip_2 , QColor(0, 0, 0));
    painter.fillRect(m_grip_4 , QColor(0, 0, 0));
    painter.fillRect(m_grip_8 , QColor(0, 0, 0));
    painter.fillRect(m_grip_5 , QColor(0, 0, 0));
    painter.fillRect(m_grip_6 , QColor(0, 0, 0));
    painter.fillRect(m_grip_9 , QColor(0, 0, 0));
    painter.fillRect(m_grip_10, QColor(0, 0, 0));
}

void TcScreenshot::mousePressEvent(QMouseEvent* event)
{
    if ( event->button() == Qt::LeftButton )
    {
        m_pressedPos = event->pos();
        if ( m_grip_1.contains(event->pos()) )
        {// 上
            m_moveHole = 1;
        }else
        if ( m_grip_2.contains(event->pos()) )
        {// 下
            m_moveHole = 2;
        }else
        if ( m_grip_4.contains(event->pos()) )
        {// 左
            m_moveHole = 4;
        }else
        if ( m_grip_8.contains(event->pos()) )
        {// 右
            m_moveHole = 8;
        }else
        if ( m_grip_5.contains(event->pos()) )
        {// 左上
            m_moveHole = 5;
        }else
        if ( m_grip_6.contains(event->pos()) )
        {// 左下
            m_moveHole = 6;
        }else
        if ( m_grip_9.contains(event->pos()) )
        {// 右上
            m_moveHole = 9;
        }else
        if ( m_grip_10.contains(event->pos()) )
        {// 右下
            m_moveHole = 10;
        }else
        if ( m_hole_rt.contains(event->pos()) )
        {// 移动
            m_moveHole = 15;
        }
    }
}

void TcScreenshot::mouseReleaseEvent(QMouseEvent*)
{
    m_moveHole = 0;
}

void TcScreenshot::mouseDoubleClickEvent(QMouseEvent* event)
{
    if ( m_hole_rt.contains(event->pos()) )
    {
        QScreen* screen = QGuiApplication::primaryScreen();
        hide();
        m_pixmap = screen->grabWindow(QApplication::desktop()->winId(),
                                      m_hole_rt.x(), m_hole_rt.y(), m_hole_rt.width(), m_hole_rt.height());
        Q_EMIT photograph(m_pixmap);
    }
}

void TcScreenshot::mouseMoveEvent(QMouseEvent* event)
{
    if ( m_grip_1.contains(event->pos()) )
    {// 上
        setCursor(Qt::SizeVerCursor);
    }else
    if ( m_grip_2.contains(event->pos()) )
    {// 下
        setCursor(Qt::SizeVerCursor);
    }else
    if ( m_grip_4.contains(event->pos()) )
    {// 左
        setCursor(Qt::SizeHorCursor);
    }else
    if ( m_grip_8.contains(event->pos()) )
    {// 右
        setCursor(Qt::SizeHorCursor);
    }else
    if ( m_grip_5.contains(event->pos()) )
    {// 左上
        setCursor(Qt::SizeFDiagCursor);
    }else
    if ( m_grip_6.contains(event->pos()) )
    {// 左下
        setCursor(Qt::SizeBDiagCursor);
    }else
    if ( m_grip_9.contains(event->pos()) )
    {// 右上
        setCursor(Qt::SizeBDiagCursor);
    }else
    if ( m_grip_10.contains(event->pos()) )
    {// 右下
        setCursor(Qt::SizeFDiagCursor);
    }else
    if ( m_hole_rt.contains(event->pos()) )
    {// 移动
        setCursor(Qt::SizeAllCursor);
    }else
    {
        setCursor(m_defaultCursor);
    }

    if ( m_moveHole > 0 )
    {
        switch(m_moveHole)
        {
        case 1: // 上
            if ( m_hole_rt.y() + event->pos().y() - m_pressedPos.y() < m_hole_rt.bottom() )
            {
                m_hole_rt.setTop(m_hole_rt.y() + event->pos().y() - m_pressedPos.y());
            }
            break;
        case 2: // 下
            m_hole_rt.setBottom(m_hole_rt.bottom() + event->pos().y() - m_pressedPos.y());
            break;
        case 4: // 左
            if ( m_hole_rt.x() + event->pos().x() - m_pressedPos.x() < m_hole_rt.right())
            {
                m_hole_rt.setLeft(m_hole_rt.x() + event->pos().x() - m_pressedPos.x());
            }
            break;
        case 8: // 右
            m_hole_rt.setRight(m_hole_rt.right() + event->pos().x() - m_pressedPos.x());
            break;
        case 5: // 左上
            m_hole_rt.setLeft(m_hole_rt.x() + event->pos().x() - m_pressedPos.x());
            m_hole_rt.setTop(m_hole_rt.y() + event->pos().y() - m_pressedPos.y());
            break;
        case 6: // 左下
            m_hole_rt.setLeft(m_hole_rt.x() + event->pos().x() - m_pressedPos.x());
            m_hole_rt.setBottom(m_hole_rt.bottom() + event->pos().y() - m_pressedPos.y());
            break;
        case 9: // 右上
            m_hole_rt.setRight(m_hole_rt.right() + event->pos().x() - m_pressedPos.x());
            m_hole_rt.setTop(m_hole_rt.y() + event->pos().y() - m_pressedPos.y());
            break;
        case 10: // 右下
            m_hole_rt.setRight(m_hole_rt.right() + event->pos().x() - m_pressedPos.x());
            m_hole_rt.setBottom(m_hole_rt.bottom() + event->pos().y() - m_pressedPos.y());
            break;

        case 15: // 移动
            QPoint pt = event->pos() - m_pressedPos;
            int x = m_hole_rt.x()+pt.x();
            int y = m_hole_rt.y()+pt.y();
            if ( x+ m_hole_rt.width() >= qApp->desktop()->screenGeometry().right() )
            {
                x = qApp->desktop()->screenGeometry().right() - m_hole_rt.width();
            }
            if ( y+ m_hole_rt.height() >= qApp->desktop()->screenGeometry().bottom() )
            {
                y = qApp->desktop()->screenGeometry().bottom() - m_hole_rt.height();
            }
            m_hole_rt.moveTo(x>=0?x:0, y>=0?y:0);
            break;
        }
        m_pressedPos = event->pos();

        makeRects();
        repaint();
    }
}
