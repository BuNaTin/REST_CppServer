#ifndef COMMAND_H
#define COMMAND_H

#include <QString>

enum class Command { ERR = 0,
                     GET,
                     POST,
                     PUT,
                     DELETE
};

inline Command CommandfromString(QString buffer) {
    if(buffer == "GET") {
        return Command::GET;
    } else
    if(buffer == "POST") {
        return Command::POST;
    } else
    if(buffer == "PUT") {
        return Command::PUT;
    } else
    if(buffer == "DELETE") {
        return Command::DELETE;
    } else {
        return Command::ERR;
    }
}

#endif // COMMAND_H
