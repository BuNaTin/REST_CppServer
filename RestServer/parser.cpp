#include "parser.h"
#include "Command.h"
#include "Mode.h"

#include <QStringList>
#include <QDebug>

Parser::Parser(QString DataFromSocket)
{
    headBuffer = DataFromSocket.split('\n')[0];
}
// парсинг приходящего http запроса
bool Parser::parseHead(Command& command, Mode& mode, int& id) {
    QStringList first = headBuffer.split(' ');
    command = CommandfromString(first[0] /* имя команды */ );
    QStringList second = first[1].split('/');
    mode = ModeFromString(second[1] /* имя выбранного режима работы */ );
    id = -1; // Error value
    if(command == Command::ERR || mode == Mode::ERR) {
        return false;
    }
    // Test mode don't have id
    if(mode == Mode::TEST) {
        return true;
    }
    // Если нехватает id
    if(second.size() < 3) {
        return false;
    }
    id = second[2].toInt();
    return true;
}
