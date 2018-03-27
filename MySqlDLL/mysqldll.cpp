#include "mysqldll.h"

/*
MySqlDLL::MySqlDLL()
{
}
*/

void MySqlDLL::printtaaPaska() {
    engine = new Engine;

    retupelle = engine->returnvalue();

    delete engine;
    engine = 0;
}

QString MySqlDLL::printtaaRetupelle() {
    return retupelle;
}
