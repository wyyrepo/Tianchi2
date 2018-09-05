#include "tcWidget.h"
#include <QStyleOption>
#include <QPainter>

void TcWidget::styleSheetPaintEvent(QWidget* widget, QPaintEvent*)
{
    QStyleOption o;
    o.initFrom(widget);
    QPainter p(widget);
    widget->style()->drawPrimitive(QStyle::PE_Widget, &o, &p, widget);
}
