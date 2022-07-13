#ifndef WINDOWSWITCH_H
#define WINDOWSWITCH_H

#include<windows.h>
#include<QThread>

class WindowSwitch :public QObject
{
    Q_OBJECT
public:
    explicit WindowSwitch();
public slots:
    void sendToSwitch();

signals:

};

#endif // WINDOWSWITCH_H
