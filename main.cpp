#include <QCoreApplication>
#include <QTcpServer>
#include "MyServer.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MyServer server; //запускаем экземпляр сервера
    //Согласен что быдлокод, не реализован даже банальный выход, но
    // я замучался с серверной частью, и это уже результат. Потому и залил

    return a.exec();
}
