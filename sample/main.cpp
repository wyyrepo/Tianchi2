#ifdef _MSC_VER
#pragma execution_character_set("utf-8")
#endif

#include "mainwindow.h"
#include "tcRunOnceChecker.h"

#include <QApplication>
#include <QStyleFactory>
#include <QMessageBox>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QApplication::setStyle(QStyleFactory::create("windowxp"));

    /// @brief 检查程序是否重复运行（第一种方式: 标准）
    TcRunOnceChecker checker("Tianchi2_Samples_App");
    if ( ! checker.isRunning(TcRunOnceChecker::ProcessList) )
    /// @brief 检查程序是否重复运行（第二种方式：简易）
    //QSharedMemory mem("Tianchi2_Samples_App");
    //if ( mem.create(1) )
    {
        // 首次运行
        MainWindow w;
        w.show();
        return app.exec();
    }else
    {
        // 已存在其它实例
        QMessageBox::critical(app.desktop(), QStringLiteral("错误"), QStringLiteral("已经有实例在运行了"));
    }
    return 0;
}
