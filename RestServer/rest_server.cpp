#include "rest_server.h"
#include "parser.h"
#include "Mode.h"
#include "Command.h"
#include "database.h"

#include <QDebug>
#include <QCoreApplication>

namespace {
    // для формирования форматированного ответа
    QString BuildResponse(int code, Command command, int id = -1, int value = -1) {
        //HTTP/1.1 404 Not found\r\n\r\nElement <%1> not found.
        QString ans = "HTTP/1.1 %1";
        switch(code) {
        case 200:
            ans = ans.arg(200) + " OK";
            break;
        case 201:
            ans = ans.arg(201) + " Created";
            break;
        case 204:
            ans = ans.arg(204) + " No content";
            break;
        case 400:
            ans = ans.arg(400) + " Bad Request";
            break;
        case 404:
            ans = ans.arg(404) + " Not found";
            break;
        default:
            ;
        }
        ans+="\r\n";
        switch(command) {
        case Command::GET:
            if(code == 200) {
                ans += QString("\r\n{\n\t\"message\":\"Item id <%1>, item value <%2>.\"\n}\n").arg(id).arg(value);
            } else {
                ans += QString("\r\n{\n\t\"message\":\"Element <%1> not found.\"\n}\n").arg(id);
            }
            break;
        case Command::PUT:
            break;
        case Command::POST:
            ans += QString("\r\n{\n\t\"id\":\"%1\"\n}\n").arg(id);
            break;
        case Command::DELETE:
            break;
        case Command::ERR:
            break;
        default:
            ;
        }
        return ans;
    }
} // namespace

Rest_Server::Rest_Server(QObject *parent) : QTcpServer(parent)
{
    dataBase = new DataBase();
    logger = new DataBaseLog();
    if(listen(QHostAddress::Any, 1234))
    {
        qDebug() << "listening...";
    }
    else
    {
        qDebug() << "error " << errorString();
    }
}

// настройка сокетов и сигналов
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

// обработка входящих запросов
void Rest_Server::onReadyRead()
{
    QTcpSocket * socket = qobject_cast<QTcpSocket*>(sender());
    Parser parser(socket->readAll());
    Command command;
    Mode mode;
    int id;
    if(!parser.parseHead(command, mode, id)){
        // if wrong accept
        QString response = "HTTP/1.1 400 Bad Request\r\n";
        socket->write(response.arg(id).toUtf8());
        socket->disconnectFromHost();
        return;
    }

    if(mode == Mode::API) {
        if(command == Command::GET) {
            int value = dataBase->Get(id);
            // If could't find
            if(value == -1) {
                socket->write(BuildResponse(404, command, id).toUtf8());
            } else {
                socket->write(BuildResponse(200, command, id, value).toUtf8());
            }
        } else
        if(command == Command::POST) {
            if(dataBase->Modify(id)) {
                logger->addNote(id,"changed");
            } else {
                logger->addNote(id,"added");
            }
            socket->write(BuildResponse(200, command, id).toUtf8());
        } else
        if(command == Command::PUT) {
            dataBase->Add(id);
            logger->addNote(id,"added");
            socket->write(BuildResponse(201, command, id).toUtf8());
        } else
        if(command == Command::DELETE) {
            if(!dataBase->Delete(id)) {
                socket->write(BuildResponse(204, command).toUtf8());
            } else {
                socket->write(BuildResponse(200, command).toUtf8());
                logger->addNote(id,"deleted");
            }
        } else {
            socket->write(BuildResponse(400, command).toUtf8());
        }
    } else
    if(mode == Mode::TEST) {
        if(command == Command::GET) {
            QString response = "HTTP/1.1 200 Ok\r\n\r\n";
            // добавление таблицы
            response += dataBase->getString();
            // добавление логов
            response += logger->getString();
            socket->write(response.toUtf8());
        } else {
            socket->write(BuildResponse(400, Command::ERR).toUtf8());
        }
    }

    socket->disconnectFromHost();
}

void Rest_Server::onDisconnected()
{
    QTcpSocket * socket = qobject_cast<QTcpSocket*>(sender());
    socket->close();
    socket->deleteLater();
}
