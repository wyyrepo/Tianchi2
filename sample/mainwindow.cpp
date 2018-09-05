#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QDebug>

#include "tcOS.h"
#include "tcChinese.h"

#include "tcAdminAuthorization.h"
#include "tcSystemInfo.h"
#include "tcWindows.h"
#include "tcAES.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent, Qt::FramelessWindowHint),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setAttribute(Qt::WA_TranslucentBackground, true); // 使用阴影时，必须把窗口设为全透明

    m_PageTurnWidget.setParent(ui->ButtonWidget);
    connect(&m_PageTurnWidget, &TcPageTurnWidget::pageTurnClicked, this, &MainWindow::evPageTurnClicked);
    m_PageTurnWidget.newButtons(1, 100, 10);

    viewHeaderSetup.append(ui->treeWidget); // 添加对 QTreeWidget 的列头设置功能

    this->showFullScreen();
}

MainWindow::~MainWindow()
{
    delete m_screenshot;
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QMessageBox::information(this, "取操作系统名称", TcOS::name());
}

void MainWindow::on_pushButton_2_clicked()
{
    QMessageBox::information(this, "取操作系统的语言", TcOS::language());
}

void MainWindow::on_pushButton_3_clicked()
{
    m_udpPort = m_udp.start();
    m_udp.setRecvMethod(this, "udpRecv");
    ui->udpMessages->append("Udp服务器启动，端口号：" + (m_udpPort >0 ? QString::number(m_udpPort) : QString("启动失败")));
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->udpMessages->append(m_udp.stop() ? "Udp服务器已经关闭" : "Udp服务器尚未启动");
}

void MainWindow::on_pushButton_5_clicked()
{
    m_udp.sendMessage(QHostAddress::LocalHost  , m_udpPort, "ABCD");
    m_udp.sendMessage(QHostAddress("localhost"), m_udpPort, "EFGH"); // 注意: 请这种写法，本机可能会收不到 !!!
    m_udp.sendMessage(QHostAddress("127.0.0.1"), m_udpPort, "IJKL");
}

void MainWindow::udpRecv(TcUdp*, const QHostAddress& Client, const QByteArray& Datagram)
{
    ui->udpMessages->append("收到Udp广播：来自" + Client.toString() + ", 收到内容：" + QString(Datagram));
}

void MainWindow::evPageTurnClicked(int pageNo)
{
    m_PageTurnWidget.newButtons(pageNo, 100, 10);//, this, SLOT(evPageTurnClicked(int)));
}

void MainWindow::on_pushButton_6_clicked()
{
    m_udp.sendBroadcast(m_udpPort, "MNOP");
    m_udp.sendBroadcast(m_udpPort, "QRST");
    m_udp.sendBroadcast(m_udpPort, "UVWX");
}

void MainWindow::on_pushButton_7_clicked()
{
  #if defined(Q_OS_WIN)
    QMessageBox::information(this, "取得多个汉字的首字母", "中华人民共和国: " + TcChinese::firstPinyins("中华人民共和国"));
  #endif
}

void MainWindow::on_pushButton_8_clicked()
{
  #if defined(Q_OS_WIN)
    QMessageBox::information(this, "取得多个汉字的全部拼音", "中华人民共和国(不含音调): " + TcChinese::toPinyin("中华人民共和国"));
    QMessageBox::information(this, "取得多个汉字的全部拼音", "中华人民共和国(含音调): " + TcChinese::toPinyin("中华人民共和国", true));
  #endif
}

void MainWindow::on_pushButton_9_clicked()
{
  #if defined(Q_OS_WIN)
    QMessageBox::information(this, "混合字符时，转换中不过滤英数符号等", "中1华2人3民4共5和6国：" + TcChinese::toChars("中1华2人3民4共5和6国"));
    QMessageBox::information(this, "混合字符时，转换中不过滤英数符号等", "中1华2人3民4共5和6国(含音调)：" + TcChinese::toChars("中1华2人3民4共5和6国", true));
  #endif
}

void MainWindow::on_pushButton_10_clicked()
{
  #if defined(Q_OS_WIN)
    QMessageBox::information(this, "中文名字翻译为英文", "诸葛亮：" + TcChinese::toEnglishName("诸葛亮", true, true, true));
  #endif
}

void MainWindow::on_pushButton_11_clicked()
{
    QMessageBox::information(this, "浮动数转金额", "12345678.9040 转换：" + QString("%L1").arg(12345678.9040, 0, 'C', 2) + "\n"
                                                + "12345678.9050 转换：" + QString("%L1").arg(12345678.9050, 0, 'C', 2));
}

void MainWindow::on_pushButton_12_clicked()
{
    QMessageBox::information(this, "确认权限", QString("有没有管理员权限: ")
                             + (TcAdminAuthorization::hasAdminRights() ? "有" : "无"));
}

void MainWindow::on_pushButton_13_clicked()
{
    #if defined(Q_OS_WIN)

        TcAdminAuthorization::execute(this, "notepad.exe", QStringList());
    #else
        QMessageBox::information(this, "没有功能", "请自行试试调用某个程序吧~~~");
    #endif
}

void MainWindow::on_pushButton_14_clicked()
{
    TcVolumeInfo vol = TcVolumeInfo::fromPath("C:\\");
    QString s = "挂载的path: " + vol.mountPath()
            + "\n文件系统类型: " + vol.fileSystemType()
            + "\n分区描述符: " + vol.volumeDescriptor()
            + "\n分区大小: " + QString::number(vol.size())
            + "\n可用空间: " + QString::number(vol.availableSize());

    QMessageBox::information(this, "获取分区信息", s);
}

void MainWindow::on_pushButton_15_clicked()
{
    TcVolumeInfo volInfo;
    QMessageBox::information(this, "挂载的path", "挂载的path，win下为盘符，即C:/ => " + volInfo.mountPath());
}

void MainWindow::on_pushButton_16_clicked()
{
    TcVolumeInfo volInfo;
    QMessageBox::information(this, "文件系统类型", "文件系统类型，在win下可能无效: " + volInfo.fileSystemType());
}

void MainWindow::on_pushButton_17_clicked()
{
    TcVolumeInfo volInfo;
    QMessageBox::information(this, "分区描述符", "分区描述符,(好像是分区的ID一类的，非盘符): " + volInfo.volumeDescriptor());
}

void MainWindow::on_pushButton_18_clicked()
{
    TcVolumeInfo volInfo;
    QMessageBox::information(this, "分区大小,单位字节", "分区大小,单位字节: " + QString::number(volInfo.size()));
}

void MainWindow::on_pushButton_19_clicked()
{
    TcVolumeInfo volInfo;
    QMessageBox::information(this, "可用空间，单位字节", "可用空间，单位字节: " + QString::number(volInfo.availableSize()));
}

void MainWindow::on_pushButton_20_clicked()
{

    QMessageBox::information(this, "当前系统的内存大小", "当前系统的内存大小: " + QString::number(TcRunInfo::installedMemory()));
}

void MainWindow::on_pushButton_21_clicked()
{
    QStringList ss;
    QList<TcVolumeInfo> vols = TcRunInfo::mountedVolumes();
    foreach(TcVolumeInfo vol, vols)
    {
        ss.append("挂载的path: " + vol.mountPath()
                + ", 文件系统类型: " + vol.fileSystemType()
                + ", 分区描述符: " + vol.volumeDescriptor()
                + ", 分区大小: " + QString::number(vol.size())
                + ", 可用空间: " + QString::number(vol.availableSize()));

    }
    QMessageBox::information(this, "当前系统的分区信息", ss.join("\n"));
}

void MainWindow::on_pushButton_22_clicked()
{
    QStringList ss;
    QList<TcProcessInfo> ps = TcRunInfo::runningProcesses();
    foreach(TcProcessInfo process, ps)
    {
        ss.append(QString("%L1: %L2").arg(process.id(), 8).arg(process.name()));
    }
    QMessageBox::information(this, "正在运行的进程列表", ss.join("\n"));
}

void MainWindow::on_pushButton_23_clicked()
{
    QMessageBox::information(this, "疑问", "请先启动记事本(notepad.exe)，将尝试杀死记事本进程");

    QList<TcProcessInfo> runinfo = TcRunInfo::runningProcesses();
    QList<TcProcessInfo> killPro;
    for( int i = 0; i < runinfo.size(); ++i )
    {
      #if defined(Q_OS_WIN)
        if ( runinfo.at(i).name().indexOf("notepad.exe") > 0 )
      #else
            //if(runinfo.at(i).name.indexOf("程序名，注意大小写") >= 0)
      #endif
        {
        killPro.append(runinfo.at(i));
        }
    }
    runinfo.clear();
    if ( ! killPro.isEmpty() )
    {
        if ( QMessageBox::Cancel == QMessageBox::warning(nullptr,
                                                         "准备",
                                                         "确定后将尝试关闭记事本",
                                                         QMessageBox::Ok | QMessageBox::Cancel) )
        {
            return;
        }
        for(int i = 0; i < killPro.size(); ++i)
        {
            TcRunInfo::killProcess(killPro.at(i));
        }
    }
    killPro.clear();
    runinfo = TcRunInfo::runningProcesses();
    for (int i = 0; i < runinfo.size(); ++i)
    {
      #if defined(Q_OS_WIN)
        if(runinfo.at(i).name().indexOf("notepad.exe") > 0)
      #else
        if(runinfo.at(i).name().indexOf("程序名，注意大小写") >= 0)
      #endif
        {
            killPro.append(runinfo.at(i));
        }
    }
    runinfo.clear();
    if ( !killPro.isEmpty() )
    {
        QMessageBox::warning(nullptr,
                             QObject::tr("错误"),
                             QObject::tr("无法结束任务！"));
        return;
    }
}

void MainWindow::on_pushButton_24_clicked()
{
    bool isLocalDevice = TcRunInfo::pathIsOnLocalDevice("C:\\");
    QMessageBox::information(this, "检查路径是不是在本地磁盘上", QString("C:\\ ") + (isLocalDevice ? "是" : "不是") + "本地磁盘");
}

void MainWindow::on_pushButton_25_clicked()
{
  #if defined(Q_OS_WIN)
    TcWindows::createLink(qApp->applicationFilePath(), TcWindows::getWinSysDir(CSIDL_DESKTOPDIRECTORY) + "\\天池演示程序");
  #endif
}

void MainWindow::on_pushButton_26_clicked()
{
    if ( m_screenshot == nullptr )
    {
        m_screenshot = new TcScreenshot();
    }

    connect(m_screenshot, &TcScreenshot::photograph, this, &MainWindow::evScreenshotPhotograph);
    m_screenshot->show();
}

void MainWindow::evScreenshotPhotograph(const QPixmap& pixmap)
{
    ui->label_3->setPixmap(pixmap);
}


void MainWindow::on_pushButton_27_clicked()
{
    ui->textEdit->clear();
    if ( ui->lineEdit->text().isEmpty() )
    {
        ui->textEdit->append("请输入明文内容。");
        ui->lineEdit->setFocus();
    }else
    if ( ui->edDesPwd->text().isEmpty() )
    {
        ui->textEdit->append("请输入密码。");
        ui->edDesPwd->setFocus();
    }else
    {
//        char sKey[] = "fujingjing";
//        const char sSrc[1024] = "China Mobile (Shenzhen) Limited 中国移动(深圳)有限公司 2003/3/20成立";
//        char sEncrypt[1024] = {0};
//        char sDecrypt[1024] = {0};

//        unsigned sEncryptLen = 0;

//        cout << "原字符串:" << sSrc << endl;
//        cout << "密钥:" << sKey << endl << endl;

        QByteArray sEncrypt;
        sEncrypt.resize(ui->lineEdit->text().toUtf8().length() * 8);

        // 加密
//        start = clock();
        TcAES   aes;
        aes.setKey(ui->edDesPwd->text().toUtf8());
        sEncrypt = aes.encryp(ui->lineEdit->text().toUtf8());
//        int sEncryptLen = DES_Encrypt(ui->lineEdit->text().toUtf8().data(), ui->lineEdit->text().toUtf8().length(),
//                                      ui->edDesPwd->text().toUtf8().data(),
//                                      sEncrypt.data());
//        sEncrypt.resize(sEncryptLen);

//        ui->textEdit->append("密文长度    ：" + QString::number(sEncryptLen));
        ui->textEdit->append("密文(Base64)：" + sEncrypt.toBase64());
        ui->textEdit->append("密文(Hex   )：" + sEncrypt.toHex()   );
        ui->textEdit->append("");
        ui->textEdit->append("");

        QByteArray sDecrypt;
        sDecrypt = aes.decryp(sEncrypt);
//        sDecrypt.resize(sEncrypt.length());
//        int sDecryptLen = DES_Decrypt(sEncrypt.data(), sEncrypt.length(),
//                                      ui->edDesPwd->text().toUtf8().data(),
//                                      sDecrypt.data());

//        sDecrypt.resize(sDecryptLen);
        ui->textEdit->append(QString("解密出明文：") + sDecrypt);

//        stop = clock();

//        cout << "加密耗时" << stop-start << "毫秒" << endl;
//        cout << "加密后:" << sEncrypt << endl << endl;

//        // 解密
//        start = clock();
//        DES_Decrypt(sEncrypt, sEncryptLen,  sKey, sDecrypt);
//        stop = clock();

//        cout << "解密耗时" << stop-start << "毫秒" << endl;
//        cout << "解密后:" << sDecrypt << endl << endl;

//        if (0 == strcmp (sSrc, sDecrypt))
//        {
//            cout << "原字符串和解密字符串相同" << endl;
//        }
//        else
//        {
//            cout << "原字符串和解密字符串不相同" << endl;
//        }
    }
}
