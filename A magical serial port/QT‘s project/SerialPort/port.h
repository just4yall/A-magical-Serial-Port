#ifndef PORT_H
#define PORT_H

#include <QWidget>
#include<QSerialPort>
#include<QMessageBox>
class Port : public QWidget
{
    Q_OBJECT
public:
    explicit Port(QWidget *parent = nullptr);
    Port(QString portName,int Baudrate);
    void closePort();
    QSerialPort* getSerial();
    void  readData();

private:
    QSerialPort *m_serial = nullptr;
signals:
    void dataRead(QByteArray data);

};

#endif // PORT_H
