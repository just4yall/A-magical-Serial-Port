#ifndef PASTE_H
#define PASTE_H


#include<windows.h>
#include<QThread>

class Paste : public QObject
{
    Q_OBJECT
public:
    explicit Paste();
public slots:
    void sendToPaste();
signals:

};

#endif // PASTE_H
