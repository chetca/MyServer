#ifndef MYSERVER_H
#define MYSERVER_H
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QByteArray>
#include <QDataStream>

class MyServer : public QObject
{
    Q_OBJECT
public:
    explicit MyServer(QObject *parent = 0);

public slots:
    void slotNewConnection(); //слот нового соединения
    void slotServerRead(); //слот для чтения данных с сокета
    void slotClientDisconnected(); //слот для приёма сигнала об отключении

private:
    QTcpServer * mTcpServer;
    QTcpSocket * mTcpSocket;
};
#endif // MYSERVER_H
