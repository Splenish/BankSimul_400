#include "session.h"

Session::Session()
{

}

void Session::setSessionAccountID(int id) {
    sessionAccountID = id;
}

int Session::getSessionAccountID() {
    return sessionAccountID;
}

void Session::setSessionCardID(int id) {
    sessionCardID = id;
}

int Session::getSessionCardID() {
    return sessionCardID;
}




