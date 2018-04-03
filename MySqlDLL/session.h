#ifndef SESSION_H
#define SESSION_H

/*#include <QString>
#include <QtSql>
#include <QDebug>
#include <QSqlDatabase>*/
#include <QStringList>

class Session
{
public:
    Session();
    void setSessionAccountID(int id);
    int getSessionAccountID();
    void setSessionCardID(int id);
    int getSessionCardID();
private:
    QStringList sessionData;
    int sessionAccountID, sessionCardID;
    QString sessionPincode, sessionFirstName, sessionLastName, sessionAddress, sessionPhoneNumber;
};

#endif // SESSION_H
