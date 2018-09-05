#include "tcDateEdit.h"

#include <QMouseEvent>

TcDateEdit::TcDateEdit(QWidget *parent)
    : QComboBox(parent)
{
    setEditable(true);

    m_calendar = new QCalendarWidget();
    QFont _font;
    _font.setPixelSize(12);
    m_calendar->setFont(_font);
    m_calendar->setContentsMargins(0, 0, 0, 0);
    //m_calendar->resize(370, 180);
  #if defined(Q_OS_WIN)
    m_calendar->resize(210, 169);
  #elif defined(Q_OS_LINUX)
    m_calendar->resize(461, 181);
  #elif defined(Q_OS_MAC)
    m_calendar->resize(210, 169);
  #else
    m_calendar->resize(210, 169);
  #endif
    m_calendar->hide();
    m_calendar->setVerticalHeaderFormat(m_calendar->NoVerticalHeader);

    connect(m_calendar, SIGNAL(clicked(QDate)), this, SLOT(calendarClicked(QDate)));
}

TcDateEdit::~TcDateEdit()
{
    delete m_calendar;
}

void TcDateEdit::focusInEvent(QFocusEvent*)
{
    //屏蔽基类事件
}

void TcDateEdit::mousePressEvent(QMouseEvent *e)
{
    //获取鼠标当前坐标及全局坐标
    int x = e->x();
    int y = e->y();
    int globx = e->globalX();
    int globy = e->globalY();

    //把日历移动到对应屏幕坐标位置、显示
    //即（屏幕x - 当前控件x）= 当前控件左端x
    //y坐标类似
    m_calendar->move(globx - x, globy + this->height() - y);
    m_calendar->setWindowFlags(Qt::Popup);
    m_calendar->setSelectedDate(this->date());
    m_calendar->show();
}

void TcDateEdit::setMinimumDate(const QDate &adate)
{
    m_calendar->setMinimumDate(adate);
    if ( ! currentText().isEmpty()
      && date() < adate )
    {
        setDate(adate);
    }
}

void TcDateEdit::setMaximumDate(const QDate &adate)
{
    m_calendar->setMaximumDate(adate);
    if ( ! currentText().isEmpty()
      && date() > adate )
    {
        setDate(adate);
    }
}

void TcDateEdit::calendarClicked(QDate _date)
{
    //日历的单击信号处理函数

    //判断combox中记录数量
    //保证其中只有一条数据
    if ( count() == 0 )
    {
        addItem(_date.toString(QLatin1String("yyyy-MM-dd")));
    }
    else
    {
        setItemData(0, QVariant::fromValue(_date.toString(QLatin1String("yyyy-MM-dd"))), Qt::DisplayRole);
    }
    setCurrentIndex(0);
    m_calendar->hide();

    Q_EMIT dateChanged(date());
}

void TcDateEdit::textChanged(const QString& text)
{
    setCurrentText(DateText(text));

    Q_EMIT dateChanged(date());
}

QDate TcDateEdit::date() const
{
    QString str = currentText().trimmed();

    QDate date = QDate::currentDate();
    int year  = date.year();
    int month = date.month();
    int day   = date.day();
    switch(str.length())
    {
    case 23:
    case 19:
        year    = str.mid( 0, 4).toInt();
        month   = str.mid( 5, 2).toInt();
        day     = str.mid( 8, 2).toInt();
        break;
    case 14:
        year    = str.mid( 0, 4).toInt();
        month   = str.mid( 4, 2).toInt();
        day     = str.mid( 6, 2).toInt();
        break;
    case 10:
        year    = str.mid( 0, 4).toInt();
        month   = str.mid( 5, 2).toInt();
        day     = str.mid( 8, 2).toInt();
        break;
    case 8:
        year    = str.mid( 0, 2).toInt();
        month   = str.mid( 3, 2).toInt();
        day     = str.mid( 6, 2).toInt();
        break;
    case 5:
        month   = str.mid( 0, 2).toInt();
        day     = str.mid( 3, 2).toInt();
        break;
    case 4:
        year    = str.toInt();
        break;
    case 2:
    case 1:
        day     = str.toInt();
        break;
    }
    return QDate(year, month, day);
}

void TcDateEdit::setDate(QDate value)
{
    clear();
    addItem(value.year() > 1900 ? value.toString(QLatin1String("yyyy-MM-dd")) : QLatin1String(""));
    setCurrentIndex(0);
    //setEditText();
}

void TcDateEdit::unsetDate()
{
    //setEditText("");
    setCurrentIndex(-1);
}

qint64 TcDateEdit::toUtcMSecsSinceEpoch()
{
    qint64 ret = 0;
    if ( ! currentText().isEmpty() )
    {
        ret = QDateTime(date()).toUTC().toMSecsSinceEpoch();
    }
    return ret;
}

qint64 TcDateEdit::toUtcLastMSecsSinceEpoch()
{
    qint64 ret = 0;
    if ( ! currentText().isEmpty() )
    {
        ret = QDateTime(date()).toUTC().toMSecsSinceEpoch() + 86399999L;
    }
    return ret;
}

QString TcDateEdit::DateText(const QString& s)
{
    QString ret;

    QString dateText = s.trimmed();

    QDate today = QDate::currentDate();
    int year  = today.year();
    int month = today.month();
    int day   = today.day();
    switch(dateText.length())
    {
    case 1: // d
    case 2: // dd
        day = dateText.toInt();
        break;
    case 3: // m/d
        month = dateText.left(1).toInt();
        day   = dateText.right(1).toInt();
        break;
    case 4: // mm/d or m/dd
        if ( dateText.mid(1, 1) == QLatin1String("/") || dateText.mid(1, 1) == QLatin1String("-") )
        {
            month = dateText.left(1).toInt();
            day   = dateText.right(2).toInt();
        }else
        if ( dateText.mid(2, 1) == QLatin1String("/") || dateText.mid(2, 1) == QLatin1String("-") )
        {
            month = dateText.left(2).toInt();
            day   = dateText.right(1).toInt();
        }else
        {
            month = 0;
            day   = 0;
        }
        break;
    case 5: // mm/dd
        month = dateText.left(2).toInt();
        day   = dateText.right(2).toInt();
        break;
    case 6: // yyyymm
    case 7: // yyyy/mm
        year  = dateText.left(4).toInt();
        month = dateText.right(2).toInt();
        break;
    case 8: // yyyymmdd
        year  = dateText.left(4).toInt();
        month = dateText.mid(4, 2).toInt();
        day   = dateText.right(2).toInt();
        break;
    case 10: // yyyy-mm-dd
        year  = dateText.left(4).toInt();
        month = dateText.mid(5, 2).toInt();
        day   = dateText.right(2).toInt();
        break;
    }
    if ( year >1900 && month >0 && month <13 && day >0 && day < 32 )
    {
        ret = QDate(year, month, day).toString(QLatin1String("yyyy-MM-dd"));
    }
    return ret;
}

