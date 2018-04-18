#include "mysqldll.h"


MySqlDLL::MySqlDLL() {
    engine = new QueryEngine;
    transactionObject = new Transaction;
    cryptoObject = new Cryptocurrency;
    //cryptoObject->setCoin("btc");
    //cryptoObject->setCoin("eth");
    //cryptoObject->setCoin("xrp");
    //cryptoObject->setCoin("bch");
    //cryptoObject->setCoin("ltc");

}

MySqlDLL::~MySqlDLL() {
    delete engine;
    delete cryptoObject;
    delete transactionObject;
    engine = 0;
    cryptoObject = 0;
    transactionObject = 0;

}

//Yhdistää ohjelman MySQL tietokantaan.
void MySqlDLL::databaseConnect() {
    //engine = new QueryEngine;
    engine->connectToDatabase();
    //delete engine;
    //engine = 0;
}

//Tarkastaa löytyykö syötetty kortti tietokannasta
bool MySqlDLL::validateCard(QString card_id) {
    //engine = new QueryEngine;
    return engine->getAccountID(card_id);
    //delete engine;
    //engine = 0;
}

//Tarkastaa vastaako käyttäjän syöttämä tunnusluku tietokannassa olevaa tunnuslukua.
//Jos tunnusluku on oikein, asettaa käyttäjän sessiodatan.
bool MySqlDLL::validatePincode(QString pincode) {
    //engine = new QueryEngine;
    return engine->checkPincode(pincode);
    //delete engine;
    //engine = 0;
}

//Palauttaa argumentin key mukaisen tiedon sessiodatasta.
//first_name, last_name, address or phone_number
QString MySqlDLL::getUserData(QString key) {
    //engine = new QueryEngine;
    return Session::getSessionUserData(key);
    //delete engine;
    //engine = 0;
}

//Katkaisee yhteyden tietokantaan ja tyhjentää sessiodatan
void MySqlDLL::disconnect() {
    engine->closeConnection();
}

//Palauttaa käyttäjän tilin saldon
float MySqlDLL::getSessionBalance() {
    return Session::getBalance();
}

//Palauttaa käyttäjän 5 viimeisintä tilitapahtumaa
QStringList MySqlDLL::getTransactions() {
    return transactionObject->lastTransactions();
}
//Palauttaa 10 tilitapahtumaa sivun mukaan. Nollas sivu on ensimmäinen sivu.
QStringList MySqlDLL::getTransactions(int page) {
    return transactionObject->lastTransactions(page);
}

//Vähentää käyttäjän tililtä nostetun summan ja tekee tietokantaan tilitapahtuman nostosta.
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

bool MySqlDLL::buyCryptoEvent(QString coin, float euroAmount) {
    cryptoObject->setCoin(coin);
    return engine->buyCryptoEur(coin, euroAmount);
}

bool MySqlDLL::sellCryptoEvent(QString coin, float cryptoAmount) {
    cryptoObject->setCoin(coin);
    return engine->sellCrypto(coin, cryptoAmount);
}

bool MySqlDLL::lockCard() {
    return engine->lockCard();
}

bool MySqlDLL::isCardLocked() {
    return engine->isCardLocked();
}


