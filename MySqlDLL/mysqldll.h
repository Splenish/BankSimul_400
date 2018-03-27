#ifndef MYSQLDLL_H
#define MYSQLDLL_H

#include "mysqldll_global.h"
#include <QString>
#include "engine.h"

class MYSQLDLLSHARED_EXPORT MySqlDLL
{

public:
    //MySqlDLL();
    void printtaaPaska();
    QString printtaaRetupelle();
private:
    QString retupelle;
    Engine* engine;

};

#endif // MYSQLDLL_H
