#ifndef DATABASE_H
#define DATABASE_H

#include <QMap>
#include <QString>

/*
 * Simple database to save and modify
 * id - value numbers
 */
class DataBase
{
public:
    DataBase();
    int Get(int id); // Err code = -1
    bool Add(int id);
    bool Modify(int id); // true - если объект изменён, false - если объект создан
    bool Delete(int id);
    QString getString();
private:
    QMap<int, int> data;
};

#endif // DATABASE_H
