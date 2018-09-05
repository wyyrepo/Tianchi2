#ifdef _MSC_VER
#pragma execution_character_set("utf-8")
#endif

#include "tcViewHeaderSetupDialog.h"
#include "ui_tcViewHeaderSetupDialog.h"

#include <QMenu>
#include <QHeaderView>
#include <QClipboard>
#include <QPushButton>

TcViewHeaderSetupDialog::TcViewHeaderSetupDialog(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::TcViewHeaderSetupDialog)
{
    ui->setupUi(this);

    ui->buttonBox->button(QDialogButtonBox::Close)->setText(QStringLiteral("关闭"));

    m_view = nullptr;
}

TcViewHeaderSetupDialog::~TcViewHeaderSetupDialog()
{
    delete ui;
}

void TcViewHeaderSetupDialog::setHeader(QTreeWidget* view, int)
{
    m_view = view;

    QTreeWidgetItem* header = view->headerItem();
    for( int i=0;i<header->columnCount();i++ )
    {
        QTreeWidgetItem* item = new QTreeWidgetItem(ui->MasterView);
        if ( i+1 == header->columnCount() && header->text(i).trimmed().isEmpty() )
        {

        }else
        {
            item->setText(0, header->text(i));
            item->setTextAlignment(0, header->textAlignment(i));
            item->setCheckState(0, view->isColumnHidden(i) ? Qt::Unchecked : Qt::Checked);
        }
    }
}

void TcViewHeaderSetupDialog::on_MasterView_itemClicked(QTreeWidgetItem* item, int)
{
    int index = ui->MasterView->indexOfTopLevelItem(item);
    m_view->setColumnHidden(index, item->checkState(0) == Qt::Unchecked);
}

void TcViewHeaderSetupDialog::on_bnUpward_clicked()
{
    foreach(QTreeWidgetItem* item, ui->MasterView->selectedItems())
    {
        int index1 = ui->MasterView->indexOfTopLevelItem(item);
        if ( index1 >0 )
        {
            int index2 = index1-1;
            item = ui->MasterView->takeTopLevelItem(index1);
            ui->MasterView->insertTopLevelItem(index2, item);
            item->setSelected(true);

            m_view->header()->swapSections(index1, index2);
        }
    }
}

void TcViewHeaderSetupDialog::on_bnDownawrd_clicked()
{
    foreach(QTreeWidgetItem* item, ui->MasterView->selectedItems())
    {
        int index1 = ui->MasterView->indexOfTopLevelItem(item);
        if ( index1 < (ui->MasterView->topLevelItemCount()-1) )
        {
            int index2 = index1+1;
            item = ui->MasterView->takeTopLevelItem(index1);
            ui->MasterView->insertTopLevelItem(index2, item);
            item->setSelected(true);

            m_view->header()->swapSections(index1, index2);
        }
    }
}

void TcViewHeaderSetupDialog::on_bnLeft_clicked()
{
    foreach(QTreeWidgetItem* item, ui->MasterView->selectedItems())
    {
        item->setTextAlignment(0, Qt::AlignLeft | Qt::AlignVCenter);

        int index = ui->MasterView->indexOfTopLevelItem(item);

        QTreeWidgetItem* header = m_view->headerItem();
        header->setTextAlignment(index, Qt::AlignLeft | Qt::AlignVCenter);
    }
}

void TcViewHeaderSetupDialog::on_bnCenter_clicked()
{
    foreach(QTreeWidgetItem* item, ui->MasterView->selectedItems())
    {
        item->setTextAlignment(0, Qt::AlignHCenter | Qt::AlignVCenter);

        int index = ui->MasterView->indexOfTopLevelItem(item);

        QTreeWidgetItem* header = m_view->headerItem();
        header->setTextAlignment(index, Qt::AlignHCenter | Qt::AlignVCenter);
    }
}

void TcViewHeaderSetupDialog::on_bnRight_clicked()
{
    foreach(QTreeWidgetItem* item, ui->MasterView->selectedItems())
    {
        item->setTextAlignment(0, Qt::AlignRight | Qt::AlignVCenter);

        int index = ui->MasterView->indexOfTopLevelItem(item);

        QTreeWidgetItem* header = m_view->headerItem();
        header->setTextAlignment(index, Qt::AlignRight | Qt::AlignVCenter);
    }
}

// ====================================================================================================================

TcViewHeaderSetup::TcViewHeaderSetup()
    : QObject()
{
}

void TcViewHeaderSetup::loadHeaderSystem(QTreeWidget* view)
{
    view->setProperty("HEADER_SYSTEM", view->header()->saveState());
}

void TcViewHeaderSetup::loadHeaderUser(QTreeWidget* view)
{
    view->setProperty("HEADER_USER", view->header()->saveState());
}

int TcViewHeaderSetup::append(QTreeWidget* view)
{
    if ( view->property("HEADER_SYSTEM").isNull() )
    {
        view->setProperty("HEADER_SYSTEM", view->header()->saveState());
    }
    if ( view->property("HEADER_USER").isNull() )
    {
        view->setProperty("HEADER_USER", view->header()->saveState());
    }

    view->setRootIsDecorated(false);
    view->sortItems(0, Qt::AscendingOrder);
    view->header()->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(view->header(), SIGNAL(customContextMenuRequested(const QPoint&)),
            this, SLOT(slot_View_header_customContextMenuRequested(const QPoint&)));
    view->setContextMenuPolicy(Qt::CustomContextMenu);

    int ret = ++m_index;
    m_viewsMutex.lock();
    m_views[ret] = view;
    m_viewsMutex.unlock();
    view->header()->setProperty("VIEW_INDEX_KEY", ret);
    return ret;
}

void TcViewHeaderSetup::remove(QTreeWidget* view)
{
    int key = view->property("VIEW_INDEX_KEY").toInt();
    m_viewsMutex.lock();
    m_views.remove(key);
    m_viewsMutex.unlock();
}

void TcViewHeaderSetup::actionCopyCell(QTreeWidget* view, QAction* action)
{
    connect(action, SIGNAL(triggered(bool)), this, SLOT(slot_View_CopyCell()));
    action->setProperty("VIEW_INDEX_KEY", view->header()->property("VIEW_INDEX_KEY").toInt());
}

void TcViewHeaderSetup::actionCopyLine(QTreeWidget* view, QAction* action)
{
    connect(action, SIGNAL(triggered(bool)), this, SLOT(slot_View_CopyLine()));
    action->setProperty("VIEW_INDEX_KEY", view->header()->property("VIEW_INDEX_KEY").toInt());
}

void TcViewHeaderSetup::actionCopyLineWithHeader(QTreeWidget* view, QAction* action)
{
    connect(action, SIGNAL(triggered(bool)), this, SLOT(slot_View_CopyLineWithHeader()));
    action->setProperty("VIEW_INDEX_KEY", view->header()->property("VIEW_INDEX_KEY").toInt());
}

void TcViewHeaderSetup::slot_View_CopyCell()
{
    int VIEW_INDEX_KEY = sender()->property("VIEW_INDEX_KEY").toInt();
    m_viewsMutex.lock();
    QTreeWidget* view = m_views.value(VIEW_INDEX_KEY);
    m_viewsMutex.unlock();
    if ( view != nullptr )
    {
        int column = view->currentColumn();
        QStringList ss;
        QString s;
        foreach(QTreeWidgetItem* item, view->selectedItems())
        {
            s = item->text(column);
            if ( s.isEmpty() )
            {
                s = item->data(column, Qt::UserRole).toString();
            }
            ss.append(s);
        }
        QClipboard* clipboard = QApplication::clipboard();
      #if defined(Q_OS_UNIX) || defined(Q_OS_LINUX)
        clipboard->setText(ss.join("\n"));
      #elif defined(Q_OS_WIN)
        clipboard->setText(ss.join("\r\n"));
      #elif defined(Q_OS_MAC)
        clipboard->setText(ss.join("\r"));
      #endif
    }
}

void TcViewHeaderSetup::slot_View_CopyLine()
{
    int VIEW_INDEX_KEY = sender()->property("VIEW_INDEX_KEY").toInt();
    m_viewsMutex.lock();
    QTreeWidget* view = m_views.value(VIEW_INDEX_KEY);
    m_viewsMutex.unlock();
    if ( view != nullptr )
    {
        QString     line;
        QStringList ss;
        QString s;
        foreach(QTreeWidgetItem* item, view->selectedItems())
        {
            line = "";
            for( int i=0;i<item->columnCount();i++ )
            {
                s = item->text(i);
                if ( s.isEmpty() )
                {
                    s = item->data(i, Qt::UserRole).toString();
                }
                line += s + "\t";
            }
            ss.append(line.trimmed());
        }
        QClipboard* clipboard = QApplication::clipboard();
      #if defined(Q_OS_UNIX) || defined(Q_OS_LINUX)
        clipboard->setText(ss.join("\n"));
      #elif defined(Q_OS_WIN)
        clipboard->setText(ss.join("\r\n"));
      #elif defined(Q_OS_MAC)
        clipboard->setText(ss.join("\r"));
      #endif
    }
}

void TcViewHeaderSetup::slot_View_CopyLineWithHeader()
{
    int VIEW_INDEX_KEY = sender()->property("VIEW_INDEX_KEY").toInt();
    m_viewsMutex.lock();
    QTreeWidget* view = m_views.value(VIEW_INDEX_KEY);
    m_viewsMutex.unlock();
    if ( view != nullptr )
    {
        QString     line;
        QStringList ss;
        QString s;
        for( int i=0; i<view->headerItem()->columnCount(); i++ )
        {
            s = view->headerItem()->text(i);
            line += s + "\t";
        }
        ss.append(line.trimmed());
        foreach(QTreeWidgetItem* item, view->selectedItems())
        {
            line = "";
            for( int i=0;i<item->columnCount();i++ )
            {
                s = item->text(i);
                if ( s.isEmpty() )
                {
                    s = item->data(i, Qt::UserRole).toString();
                }
                line += s + "\t";
            }
            ss.append(line.trimmed());
        }
        QClipboard* clipboard = QApplication::clipboard();
      #if defined(Q_OS_UNIX) || defined(Q_OS_LINUX)
        clipboard->setText(ss.join("\n"));
      #elif defined(Q_OS_WIN)
        clipboard->setText(ss.join("\r\n"));
      #elif defined(Q_OS_MAC)
        clipboard->setText(ss.join("\r"));
      #endif
    }
}

void TcViewHeaderSetup::viewHeaderPopupMenu(const QPoint& point,
                                            QTreeWidget* view,
                                            QObject* widget,
                                            const char* ColumnSetupFunc)
{
    int VIEW_INDEX_KEY = view->header()->property("VIEW_INDEX_KEY").toInt();

    Q_UNUSED(point)
    QMenu popupMenu(view->header());

    QAction* action;
    action = popupMenu.addAction(QIcon(":/res/setupdialog.png"), QStringLiteral("设置..."));
    action->setProperty("VIEW_INDEX_KEY", VIEW_INDEX_KEY);
    action->setData(-1);
    QObject::connect(action, SIGNAL(triggered(bool)), widget, ColumnSetupFunc);
    action = popupMenu.addAction(QStringLiteral("恢复系统默认"));
    action->setProperty("VIEW_INDEX_KEY", VIEW_INDEX_KEY);
    action->setData(-2);
    QObject::connect(action, SIGNAL(triggered(bool)), widget, ColumnSetupFunc);
    action = popupMenu.addAction(QStringLiteral("恢复用户默认"));
    action->setProperty("VIEW_INDEX_KEY", VIEW_INDEX_KEY);
    action->setData(-3);
    QObject::connect(action, SIGNAL(triggered(bool)), widget, ColumnSetupFunc);
    popupMenu.addSeparator();

    QTreeWidgetItem* header = view->headerItem();
    for( int i=0;i<header->columnCount();i++ )
    {
        if ( ! header->text(i).isEmpty() )
        {
            action = popupMenu.addAction(header->text(i));
            action->setCheckable(true);
            action->setProperty("VIEW_INDEX_KEY", VIEW_INDEX_KEY);
            action->setData(i);

            action->setChecked(! view->isColumnHidden(i));
            QObject::connect(action, SIGNAL(triggered(bool)), widget, ColumnSetupFunc);
        }else
        {
            break;
        }
    }
    popupMenu.exec(QCursor::pos()); // 在当前鼠标位置显示
}

void TcViewHeaderSetup::slot_View_header_customContextMenuRequested(const QPoint &point)
{
    int VIEW_INDEX_KEY = sender()->property("VIEW_INDEX_KEY").toInt();
    m_viewsMutex.lock();
    QTreeWidget* view = m_views.value(VIEW_INDEX_KEY);
    m_viewsMutex.unlock();
    if ( view != nullptr )
    {
        viewHeaderPopupMenu(point, view, this, SLOT(slot_View_header_ColumnSetup()));
    }
}

void TcViewHeaderSetup::slot_View_header_ColumnSetup()
{
    int VIEW_INDEX_KEY = sender()->property("VIEW_INDEX_KEY").toInt();
    m_viewsMutex.lock();
    QTreeWidget* view = m_views.value(VIEW_INDEX_KEY);
    m_viewsMutex.unlock();
    if ( view != nullptr )
    {
        QAction* source = qobject_cast<QAction*>(sender());
        int index = source->data().toInt();
        switch(index)
        {
        case -1:
            {
                //TcCursorWait  wait;
                TcViewHeaderSetupDialog dialog(view);
                dialog.setHeader(view);
                //wait.restore();
                dialog.exec();
            }
            break;
        case -2:
            slot_View_header_LoadSystem();
            break;
        case -3:
            slot_View_header_LoadUser();
            break;
        default:
            view->setColumnHidden(index, ! view->isColumnHidden(index));
            break;
        }
    }
}

void TcViewHeaderSetup::slot_View_header_LoadSystem()
{
    int VIEW_INDEX_KEY = sender()->property("VIEW_INDEX_KEY").toInt();
    m_viewsMutex.lock();
    QTreeWidget* view = m_views.value(VIEW_INDEX_KEY);
    m_viewsMutex.unlock();
    if ( view != nullptr )
    {
        view->header()->restoreState(view->property("HEADER_SYSTEM").toByteArray());
    }
}

void TcViewHeaderSetup::slot_View_header_LoadUser()
{
    int VIEW_INDEX_KEY = sender()->property("VIEW_INDEX_KEY").toInt();
    m_viewsMutex.lock();
    QTreeWidget* view = m_views.value(VIEW_INDEX_KEY);
    m_viewsMutex.unlock();
    if ( view != nullptr )
    {
        view->header()->restoreState(view->property("HEADER_USER").toByteArray());
    }
}


