#include "browsersearch.h"

BrowserSearch::BrowserSearch()
{
//       keybd_event(VK_CONTROL,0,0,0);//模拟ctrl按键按下
//       keybd_event(VK_MENU,0,0,0); //模拟alt按键按下
//       keybd_event(0x41,0,0,0);//模拟A键被按下
//       QThread::msleep(50);
//       keybd_event(VK_CONTROL,0,2,0); //模拟ctrl按键抬起
//       keybd_event(VK_MENU,0,2,0); //模拟alt按键抬起
//       keybd_event(0x41,0,2,0);//模拟tab键被抬起


  // setFocus(Qt::ActiveWindowFocusReason);
}

void BrowserSearch::sendKeysCOPYToSystem()
{
    keybd_event(VK_CONTROL,0,0,0);//模拟ctrl按键按下\

    keybd_event(0x43,0,0,0); //模拟C按键按下
    QThread::msleep(50);
    keybd_event(0x43,0,2,0);//模拟C键被抬起

    keybd_event(VK_CONTROL,0,2,0); //模拟ctrl按键抬起
}

QString BrowserSearch::getTextFromClipboard()
{
    return this->Clipboard->text();
}

void BrowserSearch::SearchInBrowser(QString content)
{
    //QString str = "Qt实现tcp服务器";
    //谷歌
    //QDesktopServices::openUrl(QUrl("https://google.com.hk/search?q="+content));
    //必应
    QDesktopServices::openUrl(QUrl("https://cn.bing.com/search?q="+content));
}

void BrowserSearch::startSearch()
{
    this->Clipboard = QGuiApplication::clipboard();
    this->sendKeysCOPYToSystem();
    this->SearchInBrowser(this->getTextFromClipboard());
    this->Clipboard->destroyed();

}

