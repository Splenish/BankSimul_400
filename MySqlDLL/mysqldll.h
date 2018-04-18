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
    bool validateCard(QString card_id);
    bool validatePincode(QString pincode);
    QString getUserData(QString key);
    void disconnect();
    float getSessionBalance();
    QStringList getTransactions();
    QStringList getTransactions(int page);
    bool withdrawalEvent(float amount);
    float getCoinValue(QString coin);
    float getUserCoinBalance(QString coin);
    bool buyCryptoEvent(QString coin, float euroAmount);
    bool sellCryptoEvent(QString coin, float cryptoAmount);
    bool lockCard();
    bool isCardLocked();
private:
    QueryEngine* engine;
    Transaction* transactionObject;
    Cryptocurrency* cryptoObject;

};

#endif // MYSQLDLL_H
