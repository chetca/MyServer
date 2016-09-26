#include <QCoreApplication>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QByteArray>
#include <QDataStream>
#include "MyServer.h"

MyServer::MyServer(QObject *parent) : QObject(parent) {
    mTcpServer = new QTcpServer(this); //инициализация сервера

    connect(mTcpServer, &QTcpServer::newConnection, this, &MyServer::slotNewConnection); //подключение сервера к слоту

    if(!mTcpServer->listen(QHostAddress::Any, 6666)){ //привязываем сервер к порту и айпишнику
        qDebug() << "server is not started";
    } else {
        qDebug() << "server is started";
    }
}

void MyServer::slotNewConnection() { //как только приходит сигнал, вызывается слот "NewConnection"

    mTcpSocket = mTcpServer->nextPendingConnection(); //возвращаем сокет
    mTcpSocket->write("Hello, World!!! I am a server!\r\n");//и записываем в него данные которые потом пойдут к клиенту

    connect(mTcpSocket, &QTcpSocket::readyRead, this, &MyServer::slotServerRead); //связываем сигналы со слотами
    connect(mTcpSocket, &QTcpSocket::disconnected, this, &MyServer::slotClientDisconnected);
}

void MyServer::slotServerRead() {
    while(mTcpSocket->bytesAvailable()>0) { //проверяем доступные для чтения данные

        QString str = mTcpSocket->readAll();
        QByteArray array;
        array.append(str);//записываем их в строку
        mTcpSocket->write(array); //отправляем их клиенту
    }
}

void MyServer::slotClientDisconnected() {
    mTcpSocket->close(); //в случае отключения клиента закрываем соединение
}
