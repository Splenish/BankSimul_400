#include "mysqldll.h"


MySqlDLL::MySqlDLL() {
    engine = new QueryEngine;
}

MySqlDLL::~MySqlDLL() {
    delete engine;
    engine = 0;
}

void MySqlDLL::databaseConnect() {
    //engine = new QueryEngine;
    engine->connectToDatabase();
    //delete engine;
    //engine = 0;
}

bool MySqlDLL::validateCard(QString card_id) {
    //engine = new QueryEngine;
    if(engine->getAccountID(card_id)) {
        return true;
    } else {
        return false;
    }
    //delete engine;
    //engine = 0;
}

bool MySqlDLL::validatePincode(QString pincode) {
    if(engine->checkPincode(pincode)) {
        return true;
    } else {
        return false;
    }
}

