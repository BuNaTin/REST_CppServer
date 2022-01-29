#include "database.h"

DataBase::DataBase()
{

}

int DataBase::Get(int id) {
    auto iter = data.find(id);
    // couldn't find
    if(iter == data.end()) {
        return -1;
    } else {
        return iter.value();
    }
}

bool DataBase::Add(int id) {
    if(data.contains(id)) {
        return false;
    } else {
        data.insert(id,0);
        return true;
    }
}

bool DataBase::Modify(int id) {
    if(data.contains(id)) {
        data[id]++;
        return true;
    } else {
        return false;
    }
}

bool DataBase::Delete(int id) {
    if(data.contains(id)) {
        data.erase(data.find(id));
        return true;
    } else {
        return false;
    }
}

QString DataBase::getString() {
    QString ans{"id\tvalue\n"};
    for(auto it = data.begin(); it != data.end(); ++it) {
        ans += QString("%1\t%2\n").arg(it.key()).arg(it.value());
    }
    return ans;
}
