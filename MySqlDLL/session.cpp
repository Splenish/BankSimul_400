#include "session.h"

int Session::sessionAccountID = 0;
int Session::sessionCardID = 0;
int Session::walletID = 0;
//QString Session::sessionPincode = "";
QHash<QString, QString> Session::userData;
QHash<QString, float> Session::cryptoWallet;
float Session::balance = 0;


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

void Session::setSessionUserData(QString key, QString data) {
    userData[key] = data;
}

QString Session::getSessionUserData(QString key) {
    return userData[key];
}

void Session::clearSessionData() {
    userData.clear();
    cryptoWallet.clear();
    sessionAccountID = 0;
    sessionCardID = 0;
    walletID = 0;
}

void Session::setBalance(float _balance) {
    balance = _balance;
}

float Session::getBalance() {
    return balance;
}

void Session::setSessionWalletData(QString key, float data) {
    cryptoWallet[key] = data;
}

void Session::setSessionWalletID(int ID) {
    walletID = ID;
}

float Session::getCoinBalance(QString key) {
    return cryptoWallet[key];
}
