#include <QCoreApplication>
#include "rest_server.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // прямо в конструкторе вызывается метод listen класса QTcpServer
    Rest_Server server;

    return a.exec();
}
