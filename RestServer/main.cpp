#include <QCoreApplication>
#include "rest_server.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Rest_Server server;

    return a.exec();
}
