#ifndef SWITCHDESKTOP_H
#define SWITCHDESKTOP_H

#include <QObject>
#include<windows.h>
#include<QThread>

class SwitchDesktop : public QObject
{
    Q_OBJECT
public:
    explicit SwitchDesktop(QObject *parent = nullptr);
public slots:
    void sendToSwitchDestop();
    void sendToSwitchBack();
signals:

};

#endif // SWITCHDESKTOP_H
