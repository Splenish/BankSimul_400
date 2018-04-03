#ifndef QUERYENGINE_H
#define QUERYENGINE_H

#include <QString>
#include <QStringList>
#include <QtSql>
#include <QDebug>
#include <QSqlDatabase>
#include "session.h"

class QueryEngine
{
public:
    QueryEngine();
    void connectToDatabase();
    bool getAccountID(QString card_number);
    bool checkPincode(QString pincode);
private:
    Session* newSession;
};

#endif // QUERYENGINE_H
