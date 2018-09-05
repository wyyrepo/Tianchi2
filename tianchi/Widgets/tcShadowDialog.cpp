#include "tcShadowDialog.h"
#include "ui_tcShadowDialog.h"

#include <QDesktopWidget>
#include <QMouseEvent>
#include <QPainter>

#if defined(Q_OS_WIN)
  #include <qt_windows.h>
  #include <windowsx.h>
#endif

#include <QDebug>

TcShadowDialog::TcShadowDialog(QWidget* parent, int shadowWidth)
    : QDialog(parent, Qt::FramelessWindowHint | Qt::Tool)
    , ui(new Ui::TcShadowDialog)
    , m_frameResize(false)
{
    m_shadowWidth = shadowWidth;

    ui->setupUi(this);

    setContentsMargins(0,0,0,0);
    ui->verticalLayout->setContentsMargins(shadowWidth,shadowWidth,shadowWidth,shadowWidth);

    ui->wndCaption->installEventFilter(this);
}

TcShadowDialog::~TcShadowDialog()
{
    delete ui;
}

bool TcShadowDialog::eventFilter(QObject* target, QEvent* event)
{
    if ( target == ui->wndCaption )
    {
        static bool   mousePressed = false;
        static QPoint mousePressedPos;
        if ( event->type() == QEvent::MouseButtonPress )
        {
            QMouseEvent* mouseEvent = (QMouseEvent*)event;
            if ( mouseEvent->button() == Qt::LeftButton )
            {
                mousePressed = true;
                mousePressedPos = mouseEvent->globalPos() - pos();
                return true;
            }
        }else
        if ( event->type() == QEvent::MouseButtonRelease )
        {
            mousePressed = false;
        }else
        if ( mousePressed && event->type() == QEvent::MouseMove )
        {
            QMouseEvent* mouseEvent = (QMouseEvent*)event;
            move(mouseEvent->globalPos() - mousePressedPos);
            return true;
//        }else
//        if ( event->type() == QEvent::Paint )
//        {
//            QStyleOption o;
//            o.initFrom(ui->wndCaption);
//            QPainter p(ui->wndCaption);
//            ui->wndCaption->style()->drawPrimitive(QStyle::PE_Widget, &o, &p, ui->wndCaption);
//            return true;
        }
    }
    return QDialog::eventFilter(target, event);
}

void TcShadowDialog::paintShadow(QWidget* widget, int shadowWidth)
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
        path.addRoundedRect(shadowWidth-i,
                            shadowWidth-i,
                            widget->width()-(shadowWidth-i)*2,
                            widget->height()-(shadowWidth-i)*2,
                            shadowWidth, shadowWidth, Qt::AbsoluteSize);
        color.setAlpha((shadowWidth*24) / (i+1)); //- qSqrt(i)*50);
        painter.setPen(color);
        painter.drawPath(path);
    }
}

bool TcShadowDialog::resizeEvent(const QByteArray&, void* msg, long* result, const QRect& wndRect)
{
    bool ret = false;

  #if defined(Q_OS_WIN)
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
  #endif
    return ret;
}

bool TcShadowDialog::sorptionEvent(const QByteArray&, void* msg, long*, int shadowWidth)
{
  #if defined(Q_OS_WIN)
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
  #endif
    return false;
}

QVBoxLayout* TcShadowDialog::clientLayout()
{
    return ui->DialogLayout;
}

void TcShadowDialog::setWndCaptionVisible(bool value)
{
    ui->wndCaption->setVisible(value);
}

void TcShadowDialog::initClient(QWidget* widget, const QString& captionStyle)
{
    widget->setParent(ui->DialogWidget);
    ui->DialogLayout->addWidget(widget);

    setIcon(windowIcon().pixmap(ui->edIcon->size()));
    setCaption(windowTitle());

    move((qApp->desktop()->availableGeometry().bottomRight()
          - QPoint(geometry().size().width(), geometry().size().height())) /2);

    if ( captionStyle.isEmpty() )
    {
        ui->wndCaption->setStyleSheet("QWidget#wndCaption{"
                                      "background-color:#3868BD;"
                                      "border-top-left-radius:3px;"
                                      "border-top-right-radius:3px;}");
    }else
    {
        ui->wndCaption->setStyleSheet(captionStyle);
    }

    setAttribute(Qt::WA_TranslucentBackground, m_shadowWidth >0);
        //setStyleSheet("TcShadowDialog{border: 1px solid #000000;}");
}

void TcShadowDialog::setIcon(const QPixmap& pixmap)
{
    ui->edIcon->setPixmap(pixmap);
    QMargins margins = ui->wndCaptionLayout->contentsMargins();
    if ( ! pixmap.isNull() )
    {
        margins.setLeft(1);
        ui->edIcon->setVisible(true);
    }else
    {
        margins.setLeft(9);
        ui->edIcon->setVisible(false);
    }
    ui->wndCaptionLayout->setContentsMargins(margins);
}

void TcShadowDialog::setCaption(const QString& caption)
{
    ui->edCaption->setText(caption);
}

void TcShadowDialog::paintEvent(QPaintEvent*)
{
    if ( m_shadowWidth >0 )
    {
        paintShadow(this, m_shadowWidth);
    }
}

bool TcShadowDialog::nativeEvent(const QByteArray& eventType, void* msg, long* result)
{
    return m_frameResize ? resizeEvent(eventType, msg, result, geometry()) : false;
}
