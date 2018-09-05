#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "tcShadowDialog.h"
#include "tcUdp.h"
#include "tcPageTurnWidget.h"
#include "tcScreenshot.h"
#include "tcViewHeaderSetupDialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_10_clicked();
    void on_pushButton_11_clicked();
    void on_pushButton_12_clicked();
    void on_pushButton_13_clicked();
    void on_pushButton_14_clicked();
    void on_pushButton_15_clicked();
    void on_pushButton_16_clicked();
    void on_pushButton_17_clicked();
    void on_pushButton_18_clicked();
    void on_pushButton_19_clicked();
    void on_pushButton_20_clicked();
    void on_pushButton_21_clicked();
    void on_pushButton_22_clicked();
    void on_pushButton_23_clicked();
    void on_pushButton_24_clicked();
    void on_pushButton_25_clicked();
    void on_pushButton_26_clicked();

    void on_pushButton_27_clicked();

private:
    Ui::MainWindow *ui;

    // 收发 Udp 信息
    TcUdp   m_udp;
    int     m_udpPort;
    // 注意：这里故意写成与信号发送不一样的，多了 const& ，以验证是否同样可用 ^_^
    Q_INVOKABLE void udpRecv(TcUdp* udp, const QHostAddress& Client, const QByteArray& Datagram);

    // 翻页功能
    TcPageTurnWidget    m_PageTurnWidget;
    Q_INVOKABLE void    evPageTurnClicked(int pageNo);

    // 截屏功能
    TcScreenshot*   m_screenshot = nullptr;
    Q_INVOKABLE void evScreenshotPhotograph(const QPixmap& pixmap);

    TC_PAINTSHADOW(5); // 给窗口加上阴影
    TC_WINDOWRESIZE(this); // 缩放无边框的窗口

    TcViewHeaderSetup   viewHeaderSetup;
};

#endif // MAINWINDOW_H
