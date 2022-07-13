#ifndef VOICE_H
#define VOICE_H

#include <QObject>
#include<windows.h>
#include<QThread>

class Voice : public QObject
{
    Q_OBJECT
public:
    explicit Voice(QObject *parent = nullptr);
public slots:
    void sendToStartHear();
    void sendToEndHear();
public:
    bool isHearing = false;
signals:

};

#endif // VOICE_H
