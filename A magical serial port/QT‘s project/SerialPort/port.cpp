#include "port.h"
#include<QDebug>
Port::Port(QWidget *parent)
    : QWidget{parent}
{

}

Port::Port(QString portName,int Baudrate)
{
    this->m_serial = new QSerialPort(this);
    this->m_serial->setPortName(portName);
    this->m_serial->setBaudRate(Baudrate);
    this->m_serial->setDataBits(QSerialPort::Data8);
    this->m_serial->setParity(QSerialPort::NoParity);
    this->m_serial->setStopBits(QSerialPort::OneStop);
    this->m_serial->setFlowControl(QSerialPort::SoftwareControl);
    if (m_serial->open(QIODevice::ReadWrite))
    {
        qDebug()<<"成功打开串口";
    }
    else
    {
        QMessageBox::critical(this, tr("Error"), m_serial->errorString());
    }
    connect(this->m_serial,&QSerialPort::readyRead,this,&Port::readData);

}
void Port::closePort()
{
    if (m_serial->isOpen())
        m_serial->close();
}

QSerialPort *Port::getSerial()
{
    return this->m_serial;
}

void Port::readData()
{

    emit dataRead(this->m_serial->readAll());
  // qDebug()<<QString(this->m_serial->readAll());
}
