#include <QCoreApplication>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QByteArray>
#include <QDataStream>
#include <iostream>
#include "MyServer.h"

MyServer::MyServer(QObject *parent) : QObject(parent) {
    mTcpServer = new QTcpServer(this); //инициализация сервера
    clients = new QVector<QTcpSocket*>();
    connect(mTcpServer, &QTcpServer::newConnection, this, &MyServer::slotNewConnection); //подключение сервера к слоту

    //мы слушаем весь диапазон IP-адресов на данном порту методом 'listen()'
    if(mTcpServer->listen(QHostAddress::Any, 6666)){ //привязываем сервер к порту и айпишнику
        qDebug() << "Server is started! =)";
    } else {
        qDebug() << "Server is not started! =(";
    }
}

void MyServer::slotNewConnection() { //как только приходит сигнал, вызывается слот "NewConnection"

    QTcpSocket *socket = mTcpServer->nextPendingConnection(); //возвращаем сокет
    socket->write("Hello, World!!! I am a server!\r\n");//и записываем в него данные которые потом пойдут к клиенту

    clients->push_back(socket);
    connect(socket, &QTcpSocket::readyRead, this, &MyServer::slotServerRead); //связываем сигналы со слотами
    connect(socket, &QTcpSocket::disconnected, this, &MyServer::slotClientDisconnected);

    //опционально для бинарки
    socket->write("Enter the number, and I'll tell you if it is a binary: \r\n");
}

//фактически эта функция - заглушка, нужная что бы показать что сервер работает.
//Сейчас он принимает данные от клиента, пишет их в массив и отправляет их обратно
void MyServer::slotServerRead() {
    while(true) {   //Работаем пока идут данные от клиента

        for (auto x = clients->begin(); x != clients->end(); ++x){
            if ((*x)->bytesAvailable() > 0)
            QString str = (*x)->readAll();    //Получаем данные от клиента

            //cout << "Output: " << ;
            for (auto y = clients->begin(); y != clients->end(); ++y){
                QString _tmp = str;
                if (y != x) (*y)->write(_tmp.toUtf8());        //отправляем их клиенту
            }
        }
    }
}

/*РАБОТАЕТ БАЖНО!!!! НАДО ДОДЕЛАТЬ!!!!!!
//Бинарное число
void MyServer::slotServerRead() {
    while(mTcpSocket->bytesAvailable()>0) {
        QString str = mTcpSocket->readAll();
        bool ok;
        int calc = str.toInt(&ok, 10);
        if(calc && !(calc & (calc - 1))) mTcpSocket->write("YES\r\n");
        else mTcpSocket->write("NO\r\n");
    }
}
*/

void MyServer::slotClientDisconnected() {
    mTcpSocket->close(); //в случае отключения клиента закрываем соединение
}
