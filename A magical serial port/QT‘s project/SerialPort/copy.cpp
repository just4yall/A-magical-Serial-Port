#include "copy.h"

Copy::Copy()

{

}

void Copy::sendToCopy()
{
    keybd_event(VK_CONTROL,0,0,0);//模拟ctrl按键按下

    keybd_event(0x43,0,0,0); //模拟C按键按下
    QThread::msleep(50);
    keybd_event(0x43,0,2,0);//模拟C键被抬起

    keybd_event(VK_CONTROL,0,2,0); //模拟ctrl按键抬起
}
