#ifndef PARSER_H
#define PARSER_H

#include <QString>

enum class Command;
enum class Mode;


class Parser
{
public:
    Parser(QString);

    // парсинг http запроса
    bool parseHead(Command&, Mode&, int&);
private:
    QString headBuffer;
};

#endif // PARSER_H
