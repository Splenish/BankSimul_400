#include "mysqldll.h"


MySqlDLL::MySqlDLL() {
    engine = new QueryEngine;
    transactionObject = new Transaction;
    cryptoObject = new Cryptocurrency;
    cryptoObject->setCoin("btc");
    cryptoObject->setCoin("eth");
    cryptoObject->setCoin("xrp");
    cryptoObject->setCoin("bch");
    cryptoObject->setCoin("ltc");

}

MySqlDLL::~MySqlDLL() {
    delete engine;
    delete cryptoObject;
    delete transactionObject;
    engine = 0;
    cryptoObject = 0;
    transactionObject = 0;

}

void MySqlDLL::databaseConnect() {
    //engine = new QueryEngine;
    engine->connectToDatabase();
    //delete engine;
    //engine = 0;
}

bool MySqlDLL::validateCard(QString card_id) {
    //engine = new QueryEngine;
    return engine->getAccountID(card_id);
    //delete engine;
    //engine = 0;
}

bool MySqlDLL::validatePincode(QString pincode) {
    return engine->checkPincode(pincode);
}

QString MySqlDLL::getUserData(QString key) {
    return Session::getSessionUserData(key);
}

void MySqlDLL::disconnect() {
    engine->closeConnection();
}

float MySqlDLL::getSessionBalance() {
    return Session::getBalance();
}

QStringList MySqlDLL::getTransactions() {
    return transactionObject->lastTransactions();
}

QStringList MySqlDLL::getTransactions(int page) {
    return transactionObject->lastTransactions(page);
}

bool MySqlDLL::withdrawalEvent(int amount) {
    return engine->withdrawal(amount);
}

//Returns the course of the chosen coin in EUR. If -1 is returned an error has happened.
float MySqlDLL::getCoinValue(QString coin) {
    cryptoObject->setCoin(coin);
    return cryptoObject->getCourse(coin);
}

float MySqlDLL::getUserCoinBalance(QString coin) {
    return Session::getCoinBalance(coin);
}

bool MySqlDLL::buyCryptoWithEurEvent(QString coin, float euroAmount) {
    return engine->buyCryptoEur(coin, euroAmount);
}
