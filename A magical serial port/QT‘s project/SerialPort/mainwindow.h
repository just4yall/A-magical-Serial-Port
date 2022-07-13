#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QSerialPortInfo>
#include <QSystemTrayIcon>  //t托盘类
#include <QDesktopServices> //桌面事件类
#include<QLabel>
#include<QMenu>
#include <QAction>
#include<QUrl>
#include "port.h"
#include "browsersearch.h"
#include"copy.h"
#include"paste.h"
#include"windowswitch.h"
#include"voice.h"
#include"switchdesktop.h"
#include"file.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void createActions();
    void createMenu();
    void initConfig();

private slots:
    void on_openPortBtn_clicked();

    void on_closePortBtn_clicked();

    void readData(QByteArray data);

    void on_HideBtn_clicked();
    void on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason);
    void on_showMainAction();
    void on_exitAppAction();

    void on_SaveConfigBtn_clicked();

private:
    Ui::MainWindow *ui;

    QSystemTrayIcon *mSysTrayIcon;
    QMenu *mMenu;
    QAction *mShowMainAction;
    QAction *mExitAppAction;
    QLabel *statusLabel;

    File *file;
    Port *serialPort;
    BrowserSearch *browser;
    Copy *copySomething;
    Paste *pastSomething;
    WindowSwitch *switchSomething;
    Voice *voice;
    class SwitchDesktop *switchDestop;

signals:
    void search();
    void copy();
    void paste();
    void switchWindow();
    void startHearing();
    void endHearing();
    void switchdestop();
    void switchBack();
};
#endif // MAINWINDOW_H
