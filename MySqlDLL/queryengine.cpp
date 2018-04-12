#include "queryengine.h"

QueryEngine::QueryEngine()
{

}

void QueryEngine::connectToDatabase() {
    db = QSqlDatabase::addDatabase("QMYSQL");

    db.setHostName("mysli.oamk.fi");
    db.setDatabaseName("opisk_t5raki00");
    db.setUserName("t5raki00");
    db.setPassword("DmZne33hza4ygc7C");
    /*
    db.setHostName("localhost");
    db.setDatabaseName("banksimul");
    db.setUserName("root");
    db.setPassword("root");
    */
    bool ok = db.open();
    qDebug() << "db is valid :" << db.isValid();
    qDebug() << "db database name" << db.databaseName();
    qDebug() << "db isopen error" << db.isOpenError();
    qDebug() << "db open" << ok;
}

bool QueryEngine::getAccountID(QString card_number) {
    QSqlQuery query;
    query.exec("SELECT card_id FROM card WHERE card_number = \"" + card_number + "\";");
    query.first();
    Session::setSessionCardID(query.value(0).toInt());
    QString card_id = query.value(0).toString();
    query.exec("SELECT account_id from card where card_id = " + card_id + ";");
    query.first();
    int account_id = query.value(0).toInt();

    if(query.size() > 0) {

        Session::setSessionAccountID(account_id);
        //qDebug() << newSession->getAccountSessionID();
        qDebug() << "card found";
        return true;
    } else {
        qDebug() << "Card not found";
        return false;
    }
}

bool QueryEngine::checkPincode(QString pincode) {
    QSqlQuery query;
    qDebug() << "cardID:" << Session::getSessionCardID();
    query.exec("SELECT card_id FROM card WHERE pincode = \""
               + pincode + "\" AND card_id = " + QString::number(Session::getSessionCardID()) + ";");
    if(query.size() > 0) {
        qDebug() << "oikea tunnus";
        setSessionData();
        return true;
    } else {
        qDebug() << "väärä tunnus";
        return false;
    }
}

void QueryEngine::setSessionData() {
    QSqlQuery query;
    query.exec("SELECT account.client_id, client.first_name, client.last_name, client.address, client.phone_number, account.balance FROM account INNER JOIN client ON account.client_id = client.client_id WHERE account.account_id = "
               + QString::number(Session::getSessionAccountID()) + ";");
    //qDebug() << "session query size: "  << query.size();
    query.first();
    Session::setSessionUserData("first_name", query.value(1).toString()); //first name
    Session::setSessionUserData("last_name", query.value(2).toString()); //last name
    Session::setSessionUserData("address", query.value(3).toString()); //address
    Session::setSessionUserData("phone_number", query.value(4).toString()); //phone number
    Session::setBalance(query.value(5).toFloat());

    query.exec("SELECT wallet_id, bitcoin, ethereum, ripple, bitcoin_cash, litecoin FROM cryptocurrency WHERE account_id = "
               + QString::number(Session::getSessionAccountID()) + ";");
    //qDebug() << query.size();
    query.first();
    Session::setSessionWalletID(query.value(0).toInt());
    Session::setSessionWalletData("btc", query.value(1).toFloat());
    Session::setSessionWalletData("eth", query.value(2).toFloat());
    Session::setSessionWalletData("xrp", query.value(3).toFloat());
    Session::setSessionWalletData("bch", query.value(4).toFloat());
    Session::setSessionWalletData("ltc", query.value(5).toFloat());
    //qDebug() << Session::getCoinBalance("btc");
}

QString QueryEngine::getSessionData(QString key) {
    return Session::getSessionUserData(key);
}

void QueryEngine::closeConnection() {
    if(db.isOpen()) {
        Session::setSessionAccountID(0);
        Session::setSessionCardID(0);
        Session::clearSessionData();
        db.close();
        //qDebug() << "is db open:" << db.isOpen();
    } else {
        qDebug() << "already closed";
    }
}

bool QueryEngine::withdrawal(float amount) {
    float newBalance = Session::getBalance() - amount;
    if(newBalance < 0) {
        qDebug() << "ei tarpeeks rahea";
        return false;
    } else {
        Session::setBalance(newBalance);
        QSqlQuery query;
        query.exec("UPDATE account SET balance = " + QString::number(newBalance) + " WHERE account_id = " + QString::number(Session::getSessionAccountID()) + ";");
        qDebug() << "update size:" << query.numRowsAffected();
        if (query.numRowsAffected() < 1) {
            return false;
        } else {
            query.prepare("INSERT INTO transaction (account_id, date, amount, type) VALUES (?, now(), ?, \"nosto\")");
            query.addBindValue(Session::getSessionAccountID());
            query.addBindValue(amount);
            query.exec();
            qDebug() << "insert size:" << query.numRowsAffected();
            qDebug() << "Uus saldo:" << Session::getBalance();
            if (query.numRowsAffected() < 1) {
                return false;
            }
        }
        qDebug() << "onnistu";
        return true;
    }
}

bool QueryEngine::buyCryptoEur(QString coin, float amount) {
    float cryptoAmount =  (amount / Cryptocurrency::getCourse(coin));
    qDebug() << "ripple course " << Cryptocurrency::getCourse(coin);
    qDebug() << "paljolla ostetaan " << amount;
    float newBalance = Session::getBalance() - amount;
    if(newBalance < 0) {
        qDebug() << "Not enough balance";
        return false;
    } else {
        qDebug() << "näin paljon saat cryptorahaa: " << cryptoAmount << coin;
        return true;
    }


}
