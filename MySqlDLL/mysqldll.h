#ifndef MYSQLDLL_H
#define MYSQLDLL_H


#include <QString>
#include <QtSql>
#include <QDebug>
#include <QSqlDatabase>
#include <QStringList>
#include "queryengine.h"
#include "mysqldll_global.h"
#include "session.h"
#include "transaction.h"
#include "cryptocurrency.h"

class MYSQLDLLSHARED_EXPORT MySqlDLL
{

public:
    MySqlDLL();
    ~MySqlDLL();
    void databaseConnect();
    //checks if card is tied to an account and sets card_id and account_id for the session
    bool validateCard(QString card_id);
    bool validatePincode(QString pincode);
    //first_name, last_name, address or phone_number
    QString getUserData(QString key);
    void disconnect();
    float getSessionBalance();
    QStringList getTransactions();
    QStringList getTransactions(int page);
    bool withdrawalEvent(int amount);
    float getCoinValue(QString coin);
    float getUserCoinBalance(QString coin);
    bool buyCryptoWithEurEvent(QString coin, float euroAmount);
private:
    QueryEngine* engine;
    Transaction* transactionObject;
    Cryptocurrency* cryptoObject;

};

#endif // MYSQLDLL_H
