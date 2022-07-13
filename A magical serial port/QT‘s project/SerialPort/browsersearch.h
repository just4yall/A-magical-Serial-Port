#ifndef BROWSERSEARCH_H
#define BROWSERSEARCH_H


#include<windows.h>
#include <QKeyEvent>
#include<QThread>
#include<QClipboard>
#include<QGuiApplication>
#include<QDesktopServices>
//#pragma comment(lib,"user32.lib")
class BrowserSearch : public QObject
{
    Q_OBJECT
public:
    explicit BrowserSearch();
    void sendKeysCOPYToSystem();
    QString getTextFromClipboard();
    void SearchInBrowser(QString content);
public slots:
    void startSearch();
private:
    QClipboard *Clipboard;


signals:

};

#endif // BROWSERSEARCH_H
