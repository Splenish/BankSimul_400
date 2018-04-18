#ifndef QUERYENGINE_H
#define QUERYENGINE_H

#include <QString>
#include <QStringList>
#include <QtSql>
#include <QDebug>
#include <QSqlDatabase>
#include <QVariant>
#include "session.h"
#include "cryptocurrency.h"

class QueryEngine
{
public:
    QueryEngine();
    void connectToDatabase();
    bool getAccountID(QString card_number);
    bool checkPincode(QString pincode);
    void setSessionData();
    QString getSessionData(QString key);
    void closeConnection();
    bool withdrawal(float amount);
    bool buyCryptoEur(QString coin, float amountEur);
    bool sellCrypto(QString coin, float cryptoAmount);
    bool lockCard();
    bool isCardLocked();
private:
    QSqlDatabase db;
};

#endif // QUERYENGINE_H
