#include "file.h"

File::File()
{
    this->configFile = new QFile("./config.txt",this);
    if(!configFile->exists())
    {
       qDebug()<<"文件不存在哦";
    }
    this->configFile->open(QIODeviceBase::ReadWrite);
    QString configdata;
    while(!configFile->atEnd())
    {
        configdata = configFile->readLine();
        int ComboxValue = configdata.sliced(configdata.indexOf(":")+1).toInt();
        //qDebug()<<x;
        if(configdata.contains("PortComboBox"))
        {
            this->portComBoxValue = ComboxValue;
        }
        else if(configdata.contains("BaudComboBox"))
        {
            this->BaudComBoxValue = ComboxValue;
        }
        else if(configdata.contains("Key1OnceComBox"))
        {
            this->Key1OnceComBoxValue = ComboxValue;
        }
        else if(configdata.contains("Key1TwiceComBox"))
        {
            this->Key1TwiceComBoxValue = ComboxValue;
        }
        else if(configdata.contains("Key1TrippleComBox"))
        {
            this->Key1TrippleComBoxValue = ComboxValue;
        }
        else if(configdata.contains("Key2OnceComBox"))
        {
            this->Key2OnceComBoxValue = ComboxValue;
        }
        else if(configdata.contains("Key2TwiceComBox"))
        {
            this->Key2TwiceComBoxValue = ComboxValue;
        }
        else if(configdata.contains("Key2TrippleComBox"))
        {
            this->Key2TrippleComBoxValue = ComboxValue;
        }
        else if(configdata.contains("Key12ComBox"))
        {
            this->Key12ComBoxValue = ComboxValue;
        }
        else
        {
            qDebug()<<"未知错误";
        }
    }

    this->configFile->close();
}

void File::saveConfig()
{
     this->configFile->open(QIODeviceBase::ReadWrite|QIODeviceBase::Append|QIODeviceBase::Truncate);
    this->configFile->write("PortComboBox:");
    this->configFile->write(QString::number(this->portComBoxValue).toLatin1().data());
    this->configFile->write("\n");

    this->configFile->write("BaudComboBox:");
    this->configFile->write(QString::number(this->BaudComBoxValue).toLatin1().data());
    this->configFile->write("\n");

    this->configFile->write("Key1OnceComBox:");
    this->configFile->write(QString::number(this->Key1OnceComBoxValue).toLatin1().data());
    this->configFile->write("\n");

    this->configFile->write("Key1TwiceComBox:");
    this->configFile->write(QString::number(this->Key1TwiceComBoxValue).toLatin1().data());
    this->configFile->write("\n");

    this->configFile->write("Key1TrippleComBox:");
    this->configFile->write(QString::number(this->Key1TrippleComBoxValue).toLatin1().data());
    this->configFile->write("\n");

    this->configFile->write("Key2OnceComBox:");
    this->configFile->write(QString::number(this->Key2OnceComBoxValue).toLatin1().data());
    this->configFile->write("\n");

    this->configFile->write("Key2TwiceComBox:");
    this->configFile->write(QString::number(this->Key2TwiceComBoxValue).toLatin1().data());
    this->configFile->write("\n");

    this->configFile->write("Key2TrippleComBox:");
    this->configFile->write(QString::number(this->Key2TrippleComBoxValue).toLatin1().data());
    this->configFile->write("\n");

    this->configFile->write("Key12ComBox:");
    this->configFile->write(QString::number(this->Key12ComBoxValue).toLatin1().data());
    this->configFile->write("\n");



    this->configFile->close();
}
