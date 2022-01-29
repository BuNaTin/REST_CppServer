#include "rest_server.h"
#include "parser.h"
#include "Mode.h"
#include "Command.h"
#include "database.h"

#include <QDebug>
#include <QCoreApplication>

Rest_Server::Rest_Server(QObject *parent) : QTcpServer(parent)
{
    dataBase = new DataBase();
    logger = new DataBaseLog();
    if(listen(QHostAddress::Any, 1234))
    {
        qDebug() << "listerning...";
    }
    else
    {
        qDebug() << "error " << errorString();
    }
}

void Rest_Server::incomingConnection(qintptr handle)
{
    QTcpSocket *socket = new QTcpSocket();
    socket->setSocketDescriptor(handle);
    connect(socket,
            SIGNAL(readyRead()),
            this,
            SLOT(onReadyRead()));
    connect(socket,
            SIGNAL(disconnected()),
            this,
            SLOT(onDisconnected()));
}

void Rest_Server::onReadyRead()
{
    QTcpSocket * socket = qobject_cast<QTcpSocket*>(sender());
    Parser parser(socket->readAll());
    Command command;
    Mode mode;
    int id;
    if(!parser.parseHead(command, mode, id)){
        // if wrong accept
        socket->disconnectFromHost();
        return;
    }
    //response = "HTTP/1.1 200 OK\r\n\r\nItem id <%1>, item value <%2>.";
    QString response = "";

    if(mode == Mode::API) {
        if(command == Command::GET) {
            int value = dataBase->Get(id);
            // If could't find
            if(value == -1) {
                response = "HTTP/1.1 404 WRONG\r\n\r\nDon't have item with id <%1>.";
                socket->write(response.arg(id).toUtf8());
            } else {
                response = "HTTP/1.1 200 OK\r\n\r\nItem id <%1>, item value <%2>.";
                socket->write(response.arg(id).arg(value).toUtf8());
            }
        } else
        if(command == Command::POST) {
            if(dataBase->Add(id)) {
                logger->addNote(id,"added");
            } else {
                dataBase->Modify(id);
                logger->addNote(id,"changed");
            }
            response = "HTTP/1.1 200 OK\r\n\r\nId:%1";
            socket->write(response.arg(id).toUtf8());
        } else
        if(command == Command::PUT) {
            if(!dataBase->Add(id)) {
                response = "HTTP/1.1 204 No Content\r\n";
            } else {
                response = "HTTP/1.1 201 Created\r\n";
                logger->addNote(id,"added");
            }
            socket->write(response.toUtf8());
        } else
        if(command == Command::DELETE) {
            if(!dataBase->Delete(id)) {
                response = "HTTP/1.1 204 No Content\r\n";
            } else {
                response = "HTTP/1.1 200 OK\r\n";
                logger->addNote(id,"deleted");
            }
            socket->write(response.toUtf8());
        } else {
            response = "HTTP/1.1 404 Not found\r\n";
            socket->write(response.toUtf8());
        }
    } else
    if(mode == Mode::TEST) {
        if(command == Command::GET) {
            response = "HTTP/1.1 200 OK\r\n\r\n";
            // вывод таблицы
            response += dataBase->getString();
            // вывод логов
            response += logger->getString();
        } else {
            response = "HTTP/1.1 404 Not found\r\n";
        }
        socket->write(response.toUtf8());
    }

    socket->disconnectFromHost();
}

void Rest_Server::onDisconnected()
{
    QTcpSocket * socket = qobject_cast<QTcpSocket*>(sender());
    socket->close();
    socket->deleteLater();
}
