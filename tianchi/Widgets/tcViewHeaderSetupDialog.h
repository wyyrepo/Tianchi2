/// ********************************************************************************************************************
/// @copyright Tianchi C++ source library for Qt5 (天池共享源码库)\n
/// 天池共享源码库开发组(www.qtcn.org)\n
/// @license 授权协议：请阅读天池共享源码库附带的授权协议(LICENSE.LGPLv2.1)\n
/// ********************************************************************************************************************
/// @file tcViewHeaderSetupDialog.h
/// @brief QTreeWidget 标题栏设置对话框
/// @version 1.0
/// @date 2012.12.07
/// @author 圣域天子(Jonix@qtcn.org)
///
/// ====================================================================================================================

#pragma once
#ifndef TIANCHI_TCVIEWHEADERSETUPDIALOG_H
#define TIANCHI_TCVIEWHEADERSETUPDIALOG_H

#include <QDialog>
#include <QTreeWidget>
#include <QMutex>
#include <QHash>


namespace Ui {
class TcViewHeaderSetupDialog;
}

class TcViewHeaderSetupDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TcViewHeaderSetupDialog(QWidget* parent = 0);
    virtual ~TcViewHeaderSetupDialog();

    void setHeader(QTreeWidget* view, int max=-1);

private Q_SLOTS:
    void on_bnUpward_clicked();
    void on_bnDownawrd_clicked();

    void on_MasterView_itemClicked(QTreeWidgetItem* item, int column);
    void on_bnLeft_clicked();
    void on_bnCenter_clicked();
    void on_bnRight_clicked();

private:
    Ui::TcViewHeaderSetupDialog *ui;

    QTreeWidget* m_view;
};

// ====================================================================================================================

class TcViewHeaderSetup : public QObject
{
    Q_OBJECT
public:
    TcViewHeaderSetup();

    void loadHeaderSystem(QTreeWidget* view);
    void loadHeaderUser(QTreeWidget* view);

    int  append(QTreeWidget* view);
    void remove(QTreeWidget* view);

    void actionCopyCell(QTreeWidget* view, QAction* action);
    void actionCopyLine(QTreeWidget* view, QAction* action);
    void actionCopyLineWithHeader(QTreeWidget* view, QAction* action);

public slots:
    void slot_View_CopyCell();
    void slot_View_CopyLine();
    void slot_View_CopyLineWithHeader();

private slots:
    void slot_View_header_customContextMenuRequested(const QPoint& point);
    void slot_View_header_ColumnSetup();
    void slot_View_header_LoadSystem();
    void slot_View_header_LoadUser();

private:
    int                         m_index = 0;
    QMutex                      m_viewsMutex;
    QHash<int, QTreeWidget*>    m_views;

    void    viewHeaderPopupMenu(const QPoint& point,
                                QTreeWidget* view,
                                QObject* widget,
                                const char* ColumnSetupFunc);

};

#endif // TIANCHI_TCVIEWHEADERSETUPDIALOG_H
