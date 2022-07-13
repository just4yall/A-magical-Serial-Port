#include "windowswitch.h"

WindowSwitch::WindowSwitch()

{

}

void WindowSwitch::sendToSwitch()
{
    keybd_event(VK_LMENU,0,0,0);//模拟Alt按键按下
    keybd_event(VK_TAB,0,0,0); //模拟Tab按键按下
    QThread::msleep(50);
    keybd_event(VK_TAB,0,2,0);//模拟Tab键被抬起
    keybd_event(VK_LMENU,0,2,0); //模拟Alt按键抬起
}
