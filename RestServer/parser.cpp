#include "parser.h"
#include "Command.h"
#include "Mode.h"

#include <QStringList>
#include <QDebug>

Parser::Parser(QString DataFromSocket)
{
    headBuffer = DataFromSocket.split('\n')[0];
}

bool Parser::parseHead(Command& command, Mode& mode, int& id) {
    QStringList first = headBuffer.split(' ');
    command = CommandfromString(first[0] /* which is command name */ );
    QStringList second = first[1].split('/');
    mode = ModeFromString(second[1] /* which is mode name */ );
    id = -1; // Error value
    if(command == Command::ERR || mode == Mode::ERR) {
        return false;
    }
    // Test mode don't have id
    if(mode == Mode::TEST) {
        return true;
    }
    // if don't have id num
    if(second.size() < 3) {
        return false;
    }
    id = second[2].toInt();
    return true;
}
