#ifndef UPD_SERVER_H
#define UPD_SERVER_H


#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHttpPart>
#include <QDateTime>

#include "database.h"
#include "databaselog.h"

class Rest_Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Rest_Server(QObject *parent = 0);
    void incomingConnection(qintptr handle);

signals:

public slots:
    void onReadyRead();
    void onDisconnected();
private:
    DataBase* dataBase;
    DataBaseLog* logger;
};


#endif // UPD_SERVER_H
