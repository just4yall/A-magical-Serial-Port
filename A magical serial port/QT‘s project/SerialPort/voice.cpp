#include "voice.h"

Voice::Voice(QObject *parent)
    : QObject{parent}
{

}

void Voice::sendToStartHear()
{
    keybd_event(VK_LWIN,0,0,0);//模拟win按键按下

    keybd_event(0x48,0,0,0); //模拟h按键按下
    QThread::msleep(50);
    keybd_event(0x48,0,2,0);//模拟h键被抬起

    keybd_event(VK_LWIN,0,2,0); //模拟win按键抬起
}

void Voice::sendToEndHear()
{

    keybd_event(VK_LWIN,0,0,0);//模拟win按键按下

    keybd_event(0x48,0,0,0); //模拟h按键按下
    QThread::msleep(50);
    keybd_event(0x48,0,2,0);//模拟h键被抬起

    keybd_event(VK_LWIN,0,2,0); //模拟win按键抬起

}
