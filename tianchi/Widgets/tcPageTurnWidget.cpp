#ifdef _MSC_VER
#pragma execution_character_set("utf-8")
#endif

#include "tcPageTurnWidget.h"
#include <QLayout>
#include <QVariant>
#include <QDebug>

TcPageTurnWidget::TcPageTurnWidget(QWidget* parent)
    : QObject(parent)
    , m_pageTurnBar(nullptr)
{
    m_buttonStyle = "QToolButton { background-color:white;border:1px solid rgb(222,222,222); }";
}

TcPageTurnWidget::~TcPageTurnWidget()
{
    foreach(QWidget* w, m_buttons)
    {
        delete w;
    }
    if ( m_pageTurnBar != nullptr )
    {
        m_pageTurnBar->setVisible(false);
    }
}

void TcPageTurnWidget::newButtons(int pageNo, int records, int totalPages)
{
    newButtons(pageNo, records, totalPages, this, SLOT(evPageTurn_clicked()));
}

void TcPageTurnWidget::newButtons(int pageNo, int records,
                                  int totalPages, QObject* receiver, const char* member)
{
    Q_UNUSED(records);

    QWidget* parentWidget = qobject_cast<QWidget*>(parent());

    foreach(QWidget* w, m_buttons)
    {
        delete w;
    }
    m_buttons.clear();

//    QWidget* frameWidget = qobject_cast<QWidget*>(buttonWidget->parent());
//    if ( frameWidget != nullptr )
//    {
//        frameWidget->setVisible(totalPages >1);
//    }

    if ( totalPages >1 )
    {
    //    QLabel* label = new QLabel(buttonWidget);
    //    label->setText(QString::number(records)+"条记录，共"+QString::number(totalPages)+"页");
    //    buttonWidget->layout()->addWidget(label);
    //    buttons.append(label);
        if ( totalPages > 0 )
        {
            //　分页按钮
            QToolButton* firstButton = newButton(QStringLiteral("首页"), 1, receiver, member);
            firstButton->setEnabled(pageNo >1);
            if ( pageNo >3 )
            {
                int newPageNo = pageNo-4;
                if ( newPageNo < 1 )
                {
                    newPageNo = 1;
                }
                newButton("<<", newPageNo, receiver, member);
            }
            int startPageNo = pageNo -2;
            if ( startPageNo < 1 )
            {
                startPageNo = 1;
            }
            int endPageNo = startPageNo + 4;
            if ( endPageNo > totalPages )
            {
                endPageNo = totalPages;
            }
            startPageNo = endPageNo -4;
            if ( startPageNo <= 0 )
            {
                startPageNo = 1;
            }
            for( int i=startPageNo; i<=endPageNo; ++i )
            {
                QToolButton* button = newButton(QString::number(i), i, receiver, member);
                if ( i == pageNo )
                {
                    button->setEnabled(false);
                    //button->setStyleSheet(
                    //            "QToolButton{background-color: rgb(222,222,222);border:1px solid rgb(222,222,222);}");
                    button->setStyleSheet("QToolButton{color:red; border:1px solid rgb(222,222,222);}");
                    QFont font = button->font();
                    font.setBold(true);
                    button->setFont(font);
                }
            }
            if ( (pageNo +2) < totalPages )
            {
                int newPageNo = pageNo+4;
                if ( newPageNo > totalPages )
                {
                    newPageNo = totalPages;
                }
                newButton(">>", newPageNo, receiver, member);
            }
            QToolButton* nextButton = newButton(QStringLiteral("尾页"), totalPages, receiver, member);
            nextButton->setEnabled(pageNo < totalPages);
        }
        parentWidget->update();
    }else
    if ( m_pageTurnBar != nullptr )
    {
        m_pageTurnBar->setVisible(false);
    }
}

void TcPageTurnWidget::setAutoHide(QWidget* pageTurnBar)
{
    m_pageTurnBar = pageTurnBar;
}

void TcPageTurnWidget::setButtonStyle(const QString& style)
{
    m_buttonStyle = style;
}

void TcPageTurnWidget::evPageTurn_clicked()
{
    int pageNo = 1;
    if ( sender() != nullptr && sender()->property("pageNo").isValid() )
    {
        pageNo = sender()->property("pageNo").toInt();
    }
    Q_EMIT pageTurnClicked(pageNo >1 ? pageNo : 1);
}

QToolButton* TcPageTurnWidget::newButton(const QString& caption, int pageNo, const QObject* receiver, const char* member)
{
    QWidget* parentWidget = qobject_cast<QWidget*>(parent());
    QToolButton* button = new QToolButton(parentWidget);
    button->setFont(parentWidget->font());
    button->setStyleSheet(m_buttonStyle);
    button->setText(caption);
    button->setProperty("pageNo", pageNo);
    connect(button, SIGNAL(clicked()), receiver, member);
    parentWidget->layout()->addWidget(button);
    m_buttons.append(button);
    return button;
}
