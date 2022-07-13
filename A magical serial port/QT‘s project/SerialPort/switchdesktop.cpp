#include "switchdesktop.h"

SwitchDesktop::SwitchDesktop(QObject *parent)
    : QObject{parent}
{

}

void SwitchDesktop::sendToSwitchDestop()
{
    keybd_event(VK_CONTROL,0,0,0);//模拟ctrl按键按下

    keybd_event(VK_LWIN,0,0,0); //模拟win按键按下

    keybd_event(VK_RIGHT,0,0,0); //模拟->按键按下
     QThread::msleep(50);
    keybd_event(VK_RIGHT,0,2,0); //模拟->按键抬起

    keybd_event(VK_LWIN,0,2,0);//模拟win键被抬起

    keybd_event(VK_CONTROL,0,2,0); //模拟ctrl按键抬起
}

void SwitchDesktop::sendToSwitchBack()
{
    keybd_event(VK_CONTROL,0,0,0);//模拟ctrl按键按下

    keybd_event(VK_LWIN,0,0,0); //模拟win按键按下

    keybd_event(VK_LEFT,0,0,0); //模拟<-按键按下
     QThread::msleep(50);
    keybd_event(VK_LEFT,0,2,0); //模拟<-按键抬起

    keybd_event(VK_LWIN,0,2,0);//模拟win键被抬起

    keybd_event(VK_CONTROL,0,2,0); //模拟ctrl按键抬起
}
