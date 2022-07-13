#ifndef FILE_H
#define FILE_H

#include <QFile>
#include<QDebug>
#include<QByteArray>
class File : public QObject
{
    Q_OBJECT
public:
    explicit File();
    int portComBoxValue = -1;
    int BaudComBoxValue = -1;
    int Key1OnceComBoxValue = -1;
    int Key1TwiceComBoxValue = -1;
    int Key1TrippleComBoxValue = -1;
    int Key2OnceComBoxValue = -1;
    int Key2TwiceComBoxValue = -1;
    int Key2TrippleComBoxValue = -1;
    int Key12ComBoxValue = -1;
    void saveConfig();
private:
    QFile *configFile;
signals:

};

#endif // FILE_H
