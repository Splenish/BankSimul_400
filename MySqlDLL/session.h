#ifndef SESSION_H
#define SESSION_H

/*#include <QString>
#include <QtSql>

#include <QSqlDatabase>*/
#include <QStringList>
#include <QDebug>
#include <QHash>

class Session
{
public:
    Session();
    static void setSessionAccountID(int id);
    static int getSessionAccountID();
    static void setSessionCardID(int id);
    static int getSessionCardID();
    static void setSessionUserData(QString key, QString data);
    static QString getSessionUserData(QString key);
    static void clearSessionData();
    static void setBalance(float _balance);
    static float getBalance();
    static void setSessionWalletData(QString key, float data);
    static void setSessionWalletID(int ID);
    static float getCoinBalance(QString key);
private:
    static QHash<QString, QString> userData;
    static int sessionAccountID;
    static int sessionCardID;
    static int walletID;
    static float balance;
    static QHash<QString, float> cryptoWallet;
    //static QString sessionPincode;
};

#endif // SESSION_H
