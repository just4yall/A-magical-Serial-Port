#include "paste.h"

Paste::Paste()
{

}

void Paste::sendToPaste()
{
    keybd_event(VK_CONTROL,0,0,0);//模拟ctrl按键按下

    keybd_event(0x56,0,0,0); //模拟V按键按下
    QThread::msleep(50);
    keybd_event(0x56,0,2,0);//模拟V键被抬起

    keybd_event(VK_CONTROL,0,2,0); //模拟ctrl按键抬起
}
