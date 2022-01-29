#ifndef DATABASELOG_H
#define DATABASELOG_H

#include <QString>
#include <QVector>

class DataBaseLog
{
public:
    DataBaseLog();

    QString getString();
    bool addNote(int id, QString name);
private:
    QVector<QPair<int,QString> > log;
};

#endif // DATABASELOG_H
