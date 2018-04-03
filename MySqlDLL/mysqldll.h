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

class MYSQLDLLSHARED_EXPORT MySqlDLL
{

public:
    MySqlDLL();
    ~MySqlDLL();
    void databaseConnect();
    //checks if card is tied to an account and sets card_id and account_id for the session
    bool validateCard(QString card_id);
    bool validatePincode(QString pincode);
private:
    QueryEngine* engine;
};

#endif // MYSQLDLL_H
