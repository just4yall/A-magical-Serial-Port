#include "mainwindow.h"
#include "ui_mainwindow.h"

static const char blankString[] = QT_TRANSLATE_NOOP("SettingsDialog", "N/A");
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    setWindowIcon(QIcon(":/resourse/1.jpg"));
    this->setWindowTitle("神奇的串口");
    this->setFixedSize(550,350);
    //打开的时候就要读取串口名字
    ui->PortComboBox->clear();
    QString description;
    QString manufacturer;
    QString serialNumber;
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos) {
        QStringList list;
        description = info.description();
        manufacturer = info.manufacturer();
        serialNumber = info.serialNumber();
        list << info.portName()
             << (!description.isEmpty() ? description : blankString)
             << (!manufacturer.isEmpty() ? manufacturer : blankString)
             << (!serialNumber.isEmpty() ? serialNumber : blankString)
             << info.systemLocation()
             << (info.vendorIdentifier() ? QString::number(info.vendorIdentifier(), 16) : blankString)
             << (info.productIdentifier() ? QString::number(info.productIdentifier(), 16) : blankString);
        ui->PortComboBox->addItem(list.first(), list);
    }
    ui->PortComboBox->addItem(tr("Custom"));
    ui->PortComboBox->setCurrentIndex(-1);

    this->statusLabel = new QLabel;
    //this->statusLabel->setText("欢迎使用");
    ui->statusbar->addPermanentWidget(this->statusLabel);

    ui->closePortBtn->setEnabled(false);
    //连接搜索内容的信号
    this->browser = new BrowserSearch;

    connect(this,&MainWindow::search,this->browser,&BrowserSearch::startSearch);
    //连接复制内容的信号
    this->copySomething = new Copy;

    connect(this,&MainWindow::copy,this->copySomething,&Copy::sendToCopy);
    //连接粘贴的信号
    this->pastSomething = new Paste;

    connect(this,&MainWindow::paste,this->pastSomething,&Paste::sendToPaste);
    //连接切换窗口信号
    this->switchSomething = new WindowSwitch;

    connect(this,&MainWindow::switchWindow,this->switchSomething,&WindowSwitch::sendToSwitch);
    //连接开始和结束听写输入
    this->voice = new Voice;
   // this->voice->setParent(this);

    connect(this,&MainWindow::startHearing,this->voice,&Voice::sendToStartHear);
    connect(this,&MainWindow::endHearing,this->voice,&Voice::sendToEndHear);
    //连接切换左面信号
    this->switchDestop = new  class SwitchDesktop;
    connect(this,&MainWindow::switchdestop,this->switchDestop,&SwitchDesktop::sendToSwitchDestop);
    connect(this,&MainWindow::switchBack,this->switchDestop,&SwitchDesktop::sendToSwitchBack);

    //创建文件操作对象
    this->file = new File;
    //初始化配置
    this->initConfig();
    if(this->file->portComBoxValue != -1)
    {
        this->on_openPortBtn_clicked();

    }
}

MainWindow::~MainWindow()
{
    delete ui;
    delete this->serialPort;
    delete this->file;
    delete this->serialPort;
    delete this->browser;
    delete this->copySomething;
    delete this->pastSomething;
    delete this->switchSomething;
    delete this->voice;
    delete this->switchDestop;
}

void MainWindow::createActions()
{
        mShowMainAction = new QAction("显示主界面",this);
        connect(mShowMainAction,SIGNAL(triggered()),this,SLOT(on_showMainAction()));

        mExitAppAction = new QAction("退出",this);
        connect(mExitAppAction,SIGNAL(triggered()),this,SLOT(on_exitAppAction()));
}

void MainWindow::createMenu()
{
        mMenu = new QMenu(this);
        mMenu->addAction(mShowMainAction);

        mMenu->addSeparator();

        mMenu->addAction(mExitAppAction);

        mSysTrayIcon->setContextMenu(mMenu);
}

void MainWindow::initConfig()
{
    ui->PortComboBox->setCurrentIndex( this->file->portComBoxValue);
    ui->BaudRateComboBox->setCurrentIndex(this->file->BaudComBoxValue);
    ui->Key1ComboBox->setCurrentIndex(this->file->Key1OnceComBoxValue);
    ui->Key1ComboBox_2->setCurrentIndex(this->file->Key1TwiceComBoxValue);
    ui->Key1ComboBox_3->setCurrentIndex(this->file->Key1TrippleComBoxValue);
    ui->Key2ComboBox->setCurrentIndex(this->file->Key2OnceComBoxValue);
    ui->Key2ComboBox_2->setCurrentIndex(this->file->Key2TwiceComBoxValue);
    ui->Key2ComboBox_3->setCurrentIndex(this->file->Key2TrippleComBoxValue);
    ui->Key12ComboBox->setCurrentIndex(this->file->Key12ComBoxValue);
}


void MainWindow::on_openPortBtn_clicked()
{

    this->serialPort = new Port(ui->PortComboBox->currentText(),ui->BaudRateComboBox->currentText().toInt());
    connect(this->serialPort,&Port::dataRead,this,&MainWindow::readData);
    if(this->serialPort->getSerial()->isOpen())
    {
        ui->openPortBtn->setEnabled(false);
        ui->closePortBtn->setEnabled(true);
        this->statusLabel->setText("已连接..");
    }
    else
    {
        this->statusLabel->setText("串口打开失败..");
    }
}


void MainWindow::on_closePortBtn_clicked()
{
    this->serialPort->closePort();
    if(!this->serialPort->getSerial()->isOpen())
    {
        ui->closePortBtn->setEnabled(false);
        ui->openPortBtn->setEnabled(true);
        this->statusLabel->setText("已关闭..");
    }
    else
    {
        this->statusLabel->setText("串口关闭失败..");
    }

}
void MainWindow::readData(QByteArray data)
{
    QString dataString = QString(data) ;
    ui->textShower->append(dataString);
    dataString = dataString.trimmed();
    qDebug()<<dataString;
    if(dataString == "Key1 Once")
    {
        switch(ui->Key1ComboBox->currentIndex())
        {
        case 0:
        {
            //一键切换程序
            emit this->switchWindow();
            break;
        }
        case 1:
        {
            //听写输入
            if(! this->voice->isHearing)
            {
                emit this->startHearing();
                this->voice->isHearing = true;
            }
            else if(this->voice->isHearing)
            {
                emit this->endHearing();
                this->voice->isHearing = false;
            }

            break;
        }
        case 2:
        {
            //浏览器搜索
            emit this->search();
            break;
        }
        case 3:
        {
            //一键复制
            emit this->copy();
            break;
        }
        case 4:
        {
            //一键粘贴
            emit this->paste();
            break;
        }
        default: break;
        }
    }
    else if(dataString == "Key1 Twice")
    {
        switch(ui->Key1ComboBox_2->currentIndex())
        {
        case 0:
        {
            //一键切换程序
            emit this->switchWindow();
            break;
        }
        case 1:
        {
            //听写输入
            if(! this->voice->isHearing)
            {
                emit this->startHearing();
                this->voice->isHearing = true;
            }
            else if(this->voice->isHearing)
            {
                emit this->endHearing();
                this->voice->isHearing = false;
            }
            break;
        }
        case 2:
        {
            //浏览器搜索
            emit this->search();
            break;
        }
        case 3:
        {
            //一键复制
            emit this->copy();
            break;
        }
        case 4:
        {
            //一键粘贴
            emit this->paste();
            break;
        }
        default: break;
        }
    }
    else if(dataString == "Key1 Tripple")
    {
        switch(ui->Key1ComboBox_3->currentIndex())
        {
        case 0:
        {
            //一键切换程序
            emit this->switchWindow();
            break;
        }
        case 1:
        {
            //听写输入
            if(! this->voice->isHearing)
            {
                emit this->startHearing();
                this->voice->isHearing = true;
            }
            else if(this->voice->isHearing)
            {
                emit this->endHearing();
                this->voice->isHearing = false;
            }
            break;
        }
        case 2:
        {
            //浏览器搜索
            emit this->search();
            break;
        }
        case 3:
        {
            //一键复制
            emit this->copy();
            break;
        }
        case 4:
        {
            //一键粘贴
            emit this->paste();
            break;
        }
        default: break;
        }
    }
    else if(dataString == "Key2 Once")
    {
        switch(ui->Key2ComboBox->currentIndex())
        {
        case 0:
        {
            //一键切换程序
            emit this->switchWindow();
            break;
        }
        case 1:
        {
            //听写输入
            if(! this->voice->isHearing)
            {
                emit this->startHearing();
                this->voice->isHearing = true;
            }
            else if(this->voice->isHearing)
            {
                emit this->endHearing();
                this->voice->isHearing = false;
            }

            break;
        }
        case 2:
        {
            //浏览器搜索
            emit this->search();
            break;
        }
        case 3:
        {
            //一键复制
            emit this->copy();
            break;
        }
        case 4:
        {
            //一键粘贴
            emit this->paste();
            break;
        }
        default: break;
        }
    }
    else if(dataString == "Key2 Twice")
    {
        switch(ui->Key2ComboBox_2->currentIndex())
        {
        case 0:
        {
            //一键切换程序
            emit this->switchWindow();
            break;
        }
        case 1:
        {
            //听写输入
            if(! this->voice->isHearing)
            {
                emit this->startHearing();
                this->voice->isHearing = true;
            }
            else if(this->voice->isHearing)
            {
                emit this->endHearing();
                this->voice->isHearing = false;
            }
            break;
        }
        case 2:
        {
            //浏览器搜索
            emit this->search();
            break;
        }
        case 3:
        {
            //一键复制
            emit this->copy();
            break;
        }
        case 4:
        {
            //一键粘贴
            emit this->paste();
            break;
        }
        default: break;
        }
    }
    else if(dataString == "Key2 Tripple")
    {
        switch(ui->Key2ComboBox_3->currentIndex())
        {
        case 0:
        {
            //一键切换程序
            emit this->switchWindow();
            break;
        }
        case 1:
        {
            //听写输入
            if(! this->voice->isHearing)
            {
                emit this->startHearing();
                this->voice->isHearing = true;
            }
            else if(this->voice->isHearing)
            {
                emit this->endHearing();
                this->voice->isHearing = false;
            }
            break;
        }
        case 2:
        {
            //浏览器搜索
            emit this->search();
            break;
        }
        case 3:
        {
            //一键复制
            emit this->copy();
            break;
        }
        case 4:
        {
            //一键粘贴
            emit this->paste();
            break;
        }
        default: break;
        }
    }
    else if(dataString == "Key1+Key2")
    {
        switch(ui->Key12ComboBox->currentIndex())
        {
        case 0:
        {
            //一键切换桌面
            emit this->switchdestop();
            break;
        }

        default: break;
        }
    }
    else if(dataString == "Key2+Key1")
    {
        switch(ui->Key12ComboBox->currentIndex())
        {
        case 0:
        {
            //一键切回桌面
           emit this->switchBack();
            break;
        }

        default: break;
        }
    }

}

void MainWindow::on_HideBtn_clicked()
{


    this->hide();
    //emit this->search();
    //新建QSystemTrayIcon对象
    this->mSysTrayIcon = new QSystemTrayIcon(this);
    //新建托盘要显示的icon
    QIcon icon = QIcon(":/resourse/1.jpg");
    //将icon设到QSystemTrayIcon对象中
    this->mSysTrayIcon->setIcon(icon);
    //当鼠标移动到托盘上的图标时，会显示此处设置的内容
    this->mSysTrayIcon->setToolTip("一个神奇的串口指令系统~");
    //给QSystemTrayIcon添加槽函数
    connect(mSysTrayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason)));

    //建立托盘操作的菜单
    createActions();
    createMenu();
    //在系统托盘显示此对象
    mSysTrayIcon->show();
}

void MainWindow::on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason)
    {
    case QSystemTrayIcon::Trigger:
        //mSysTrayIcon->showMessage("Message Title","欢迎使用此程序", QSystemTrayIcon::Information,1000);
        break;
    case QSystemTrayIcon::DoubleClick:
        this->show();
        this->mSysTrayIcon->hide();
        break;
    default:
        break;
    }
}

void MainWindow::on_showMainAction()
{
    this->show();
    this->mSysTrayIcon->hide();
}

void MainWindow::on_exitAppAction()
{
    exit(0);
}


void MainWindow::on_SaveConfigBtn_clicked()
{
    this->file->portComBoxValue = ui->PortComboBox->currentIndex();
    this->file->BaudComBoxValue = ui->BaudRateComboBox->currentIndex();
    this->file->Key1OnceComBoxValue = ui->Key1ComboBox->currentIndex();
    this->file->Key1TwiceComBoxValue = ui->Key1ComboBox_2->currentIndex();
    this->file->Key1TrippleComBoxValue = ui->Key1ComboBox_3->currentIndex();
    this->file->Key2OnceComBoxValue = ui->Key2ComboBox->currentIndex();
    this->file->Key2TwiceComBoxValue = ui->Key2ComboBox_2->currentIndex();
    this->file->Key2TrippleComBoxValue = ui->Key2ComboBox_3->currentIndex();
    this->file->Key12ComBoxValue = ui->Key12ComboBox->currentIndex();
    this->file->saveConfig();
}


