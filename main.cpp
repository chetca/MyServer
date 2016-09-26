#include <QCoreApplication>
#include <QTcpServer>
#include "MyServer.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MyServer server;

    return a.exec();
}
