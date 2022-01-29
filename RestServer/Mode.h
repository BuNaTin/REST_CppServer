
#pragma once

#ifndef MODE_H
#define MODE_H

#include <QString>

enum class Mode { ERR = 0,
                  API,
                  TEST
};

inline Mode ModeFromString(QString buffer){
   if(buffer == "api") {
       return Mode::API;
   } else
   if(buffer == "test") {
       return Mode::TEST;
   } else {
       return Mode::ERR;
   }
}

#endif // MODE_H
