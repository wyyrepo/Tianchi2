#include "tcStyleToolDialog.h"
#include "ui_tcStyleToolDialog.h"

#include <QDesktopWidget>
#include <QMouseEvent>
#include <QPainter>
#include <qt_windows.h>
#include <windowsx.h>

#include <QDebug>

void TcStyleToolDialog::paintShadow(QWidget* widget, int shadowWidth)
{
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    path.addRoundedRect(shadowWidth, shadowWidth, widget->width()-shadowWidth*2, widget->height()-shadowWidth*2,
                        shadowWidth, shadowWidth);

    QPainter painter(widget);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.fillPath(path, QBrush(Qt::white));

    QColor color(0, 0, 0, 250);
    for(int i=0; i<shadowWidth; ++i)
    {
        QPainterPath path;
        path.setFillRule(Qt::WindingFill);
        path.addRoundedRect(shadowWidth -i,
                            shadowWidth -i,
                            widget->width()-(shadowWidth -i)*2,
                            widget->height()-(shadowWidth -i)*2,
                            shadowWidth, shadowWidth, Qt::AbsoluteSize);
        color.setAlpha((shadowWidth*24) / (i+1)); //- qSqrt(i)*50);
        painter.setPen(color);
        painter.drawPath(path);
    }
}

bool TcStyleToolDialog::resizeEvent(const QByteArray&, void* msg, long* result, const QRect& wndRect)
{
    bool ret = false;
    MSG* message = (MSG*) msg;
    switch(message->message)
    {
    case WM_NCHITTEST:
        int xPos = GET_X_LPARAM(message->lParam) - wndRect.x();
        int yPos = GET_Y_LPARAM(message->lParam) - wndRect.y();
        //if ( childAt(xPos, yPos) == ? ) // ? 为桌面控件名，即可实现拖动，但无法双击缩放
        //{
        //    // 移动
        //    *result = HTCAPTION;
        //}else
        //{
        //    return false;
        //}
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

bool TcStyleToolDialog::sorptionEvent(const QByteArray&, void* msg, long*, int shadowWidth)
{
    MSG* message = (MSG*) msg;
    if ( message->message == WM_MOVING )
    {
        LPRECT prc = (LPRECT)message->lParam;
        int wndWidth  = prc->right - prc->left;
        int wndHeight = prc->bottom - prc->top;

        const int distance = 16;

        static bool sorptionX = false;
        static bool sorptionY = false;
        static int startX;
        static int startY;
        if ( abs(prc->left) <= distance )
        {
            prc->left = -shadowWidth;
            prc->right = wndWidth-shadowWidth;
            if ( ! sorptionX )
            {
                sorptionX = true;
                startX = QCursor::pos().x();
            }
        }
        if ( abs(prc->right - qApp->desktop()->availableGeometry().right()) <= distance )
        {
            prc->left = qApp->desktop()->availableGeometry().right() - wndWidth + shadowWidth;
            prc->right = qApp->desktop()->availableGeometry().right() + shadowWidth;
            if ( ! sorptionX )
            {
                sorptionX = true;
                startX = QCursor::pos().x();
            }
        }
        if ( abs(prc->top) <= distance )
        {
            prc->top = -shadowWidth;
            prc->bottom = wndHeight-shadowWidth;
            if ( ! sorptionY )
            {
                sorptionY = true;
                startY = QCursor::pos().y();
            }
        }
        if ( abs(prc->bottom - qApp->desktop()->availableGeometry().bottom()) <= distance )
        {
            prc->top = qApp->desktop()->availableGeometry().bottom() - wndHeight + shadowWidth;
            prc->bottom = qApp->desktop()->availableGeometry().bottom() + shadowWidth;
            if ( ! sorptionY )
            {
                sorptionY = true;
                startY = QCursor::pos().y();
            }
        }
        if ( sorptionX )
        {
            int newX = QCursor::pos().x() - startX;
            if ( abs(newX) > distance )
            {
                prc->left = prc->left + newX - shadowWidth;
                prc->right = prc->left + wndWidth;

                sorptionX = false;
            }
        }
        if ( sorptionY )
        {
            int newY = QCursor::pos().y() - startY;
            if ( abs(newY) > distance )
            {
                prc->top = prc->top + newY - shadowWidth;
                prc->bottom = prc->top + wndHeight;

                sorptionY = false;
            }
        }
    }
    return false;
}

TcStyleToolDialog::TcStyleToolDialog(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::TcStyleToolDialog)
    , m_dialogResize(false)
{
    ui->setupUi(this);

    setWindowFlags( windowFlags() | Qt::FramelessWindowHint );

    ui->DialogWidget->setAttribute(Qt::WA_TranslucentBackground, true);

    //QMargins shadowMargins = ui->dialogLayout->contentsMargins();

    m_shadowWidth = 0; //(shadowMargins.left()+shadowMargins.top()+shadowMargins.right()+shadowMargins.bottom())/4;
}

TcStyleToolDialog::~TcStyleToolDialog()
{
    delete ui;
}

QLayout* TcStyleToolDialog::clientLayout()
{
    return ui->clientLayout;
}

void TcStyleToolDialog::setShadowWidth(int shadowWidth)
{
    m_shadowWidth = shadowWidth;
    setContentsMargins(0,0,0,0);
    ui->dialogLayout->setContentsMargins(shadowWidth, shadowWidth, shadowWidth, shadowWidth);

    setAttribute(Qt::WA_TranslucentBackground, shadowWidth >0);
}

void TcStyleToolDialog::initClient(QWidget* widget)
{
    widget->setParent(ui->DialogWidget);
    ui->clientLayout->addWidget(widget);

    move((qApp->desktop()->availableGeometry().bottomRight()
          - QPoint(geometry().size().width(), geometry().size().height())) /2);
}

void TcStyleToolDialog::paintEvent(QPaintEvent*)
{
    if ( m_shadowWidth >0 )
    {
        paintShadow(this, m_shadowWidth);
    }
}

bool TcStyleToolDialog::nativeEvent(const QByteArray& eventType, void* msg, long* result)
{
    MSG* message = (MSG*) msg;
    switch(message->message)
    {
    case WM_NCHITTEST:
        int xPos = GET_X_LPARAM(message->lParam) - geometry().x();
        int yPos = GET_Y_LPARAM(message->lParam) - geometry().y();
        if ( isMoveBar(childAt(xPos, yPos)) )
        {
            *result = HTCAPTION;
            return true;
        }else
        if ( m_dialogResize )
        {
            return resizeEvent(eventType, msg, result, QRect(geometry().x()+m_shadowWidth,
                                                             geometry().y()+m_shadowWidth,
                                                             geometry().width()-m_shadowWidth-m_shadowWidth,
                                                             geometry().height()-m_shadowWidth-m_shadowWidth));
        }
    }
    return QDialog::nativeEvent(eventType, msg, result);
}
