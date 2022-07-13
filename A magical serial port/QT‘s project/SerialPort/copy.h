#ifndef COPY_H
#define COPY_H

#include<windows.h>
#include<QThread>

class Copy : public QObject
{
    Q_OBJECT
public:
    explicit Copy();
public slots:
    void sendToCopy();

signals:

};

#endif // COPY_H
