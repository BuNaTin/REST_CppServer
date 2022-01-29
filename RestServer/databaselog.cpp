#include "databaselog.h"

DataBaseLog::DataBaseLog()
{

}

bool DataBaseLog::addNote(int id, QString name) {
    log.push_back(QPair<int, QString> (id, name));
    return true;
}

QString DataBaseLog::getString() {
    QString ans{};
    for(auto it = log.begin(); it != log.end(); ++it) {
        ans += QString("item with id <%1> has been %2\n").arg(it->first).arg(it->second);
    }
    return ans;
}
//item with id <> has been added, item with id <> has been deleted, item with id <> has been changed
