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
    if(ok)
        qDebug() << "Connection open";
    else
        qDebug() << "Connection failed to open";
    //qDebug() << "db is valid :" << db.isValid();
    //qDebug() << "db database name" << db.databaseName();
    //qDebug() << "db isopen error" << db.isOpenError();
    //qDebug() << "db open" << ok;
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
    query.setNumericalPrecisionPolicy(QSql::HighPrecision);
    query.exec("SELECT account.client_id, client.first_name, client.last_name, client.address, client.phone_number, account.balance FROM account INNER JOIN client ON account.client_id = client.client_id WHERE account.account_id = "
               + QString::number(Session::getSessionAccountID()) + ";");
    //qDebug() << "session query size: "  << query.size();
    query.first();
    Session::setSessionUserData("first_name", query.value(1).toString()); //first name
    Session::setSessionUserData("last_name", query.value(2).toString()); //last name
    Session::setSessionUserData("address", query.value(3).toString()); //address
    Session::setSessionUserData("phone_number", query.value(4).toString()); //phone number
    Session::setBalance(query.value(5).toFloat());

    query.exec("SELECT wallet_id, btc, eth, xrp, bch, ltc FROM cryptocurrency WHERE account_id = "
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
    float newBalance = (float)Session::getBalance() - (float)amount;
    qDebug() << "tää on uus balance withdrawalis:" << newBalance;
    if(newBalance < 0) {
        qDebug() << "ei tarpeeks rahea";
        return false;
    } else {
        db.transaction();
        QSqlQuery query;
        query.setNumericalPrecisionPolicy(QSql::HighPrecision);
        query.exec("UPDATE account SET balance = " + QString::number(newBalance) + " WHERE account_id = " + QString::number(Session::getSessionAccountID()) + ";");
        //qDebug() << "update size:" << query.numRowsAffected();
        if (query.numRowsAffected() < 1) {
            db.rollback();
            qDebug() << "Withdrawal failed";
            return false;
        } else {
            query.prepare("INSERT INTO transaction (account_id, date, amount, type) VALUES (?, now(), ?, \"nosto\")");
            query.addBindValue(Session::getSessionAccountID());
            query.addBindValue(amount);
            query.exec();
            //qDebug() << "insert size:" << query.numRowsAffected();
            if (query.numRowsAffected() < 1) {
                db.rollback();
                qDebug() << "Transaction failed";
                return false;
            }
        }
        qDebug() << "Transaction succeeded";
        Session::setBalance(newBalance);
        //qDebug() << "Uus saldo:" << Session::getBalance();
        db.commit();
        return true;
    }
}

bool QueryEngine::buyCryptoEur(QString coin, float amountEur) {
    float cryptoAmount =  (amountEur / Cryptocurrency::getCourse(coin));
    //qDebug() << "ripple course " << Cryptocurrency::getCourse(coin);
    //qDebug() << "paljolla ostetaan " << amount;
    float newBalance = Session::getBalance() - amountEur;
    if(newBalance < 0) {
        qDebug() << "Not enough balance";
        return false;
    } else {
        db.transaction();
        qDebug() << "näin paljon saat cryptorahaa: " << cryptoAmount << coin;
        float newCryptoBalance = Session::getCoinBalance(coin) + cryptoAmount;
        //qDebug() << "Vanha kryptobalance" << Session::getCoinBalance(coin);
        //qDebug() << "uus kryptobalance" << newCryptoBalance;
        QSqlQuery query;
        query.setNumericalPrecisionPolicy(QSql::HighPrecision);
        query.exec("UPDATE cryptocurrency SET " + coin + " = " + QString::number(newCryptoBalance) + " WHERE account_id = " + QString::number(Session::getSessionAccountID()) + ";");
        //qDebug() << "num rows affected" << query.numRowsAffected();
        if(query.numRowsAffected() < 1) {
            qDebug() << "Transaction failed (failed to update cryptocurrency)";
            db.rollback();
            return false;
        } else {
            query.exec("UPDATE account SET balance = " + QString::number(newBalance) + " WHERE account_id = " + QString::number(Session::getSessionAccountID()) + ";");
            if(query.numRowsAffected() < 1) {
                qDebug() << "Transaction failed (failed to update balance)";
                db.rollback();
                return false;
            } else {
                query.prepare("INSERT INTO transaction (account_id, date, amount, type) VALUES (?, now(), ?, ?);");
                query.addBindValue(Session::getSessionAccountID());
                query.addBindValue(-amountEur);
                QString typeStr = coin + "/osto";
                query.addBindValue(typeStr);
                query.exec();
                if(query.numRowsAffected() < 1) {
                    db.rollback();
                    qDebug() << "Transaction failed (failed to create transaction)";
                    return false;
                } else {
                    Session::setBalance(newBalance);
                    qDebug() << "Purchase succeeded";
                    return true;
                }
            }
        }
    }
}

bool QueryEngine::sellCrypto(QString coin, float cryptoAmount) {
    float gainedEur = cryptoAmount * Cryptocurrency::getCourse(coin);
    float newEurBalance = Session::getBalance() + gainedEur;
    qDebug() << "uus eurobalance myynnissä:" << newEurBalance;
    float newCryptoBalance = Session::getCoinBalance(coin) - cryptoAmount;
    if(newCryptoBalance < 0) {
        qDebug() << "Not enough" << coin << "balance";
        return false;
    } else {
        qDebug() << "saadut eurot" << gainedEur;
        db.transaction();
        QSqlQuery query;
        query.setNumericalPrecisionPolicy(QSql::HighPrecision);
        query.exec("UPDATE cryptocurrency SET " + coin + " = " + QString::number(newCryptoBalance) + " WHERE account_id = " + QString::number(Session::getSessionAccountID()) + ";");
        if(query.numRowsAffected() < 1) {
            qDebug() << "Transaction failed (failed to update crypto balance)";
            db.rollback();
            return false;
        } else {
            query.exec("UPDATE account SET balance = " + QString::number(newEurBalance) + " WHERE account_id = " + QString::number(Session::getSessionAccountID()) + ";");
            if(query.numRowsAffected() < 1) {
                qDebug() << "Transaction failed (failed to update balance)";
                db.rollback();
                return false;
            } else {
                query.prepare("INSERT INTO transaction (account_id, date, amount, type) VALUES (?, now(), ?, ?);");
                query.addBindValue(Session::getSessionAccountID());
                query.addBindValue(gainedEur);
                QString typeStr = coin + "/osto";
                query.addBindValue(typeStr);
                query.exec();
                if(query.numRowsAffected() < 1) {
                    qDebug() << "Transaction failed (failed to create transaction)";
                    db.rollback();
                    return false;
                } else {
                    qDebug() << "Sell succeeded";
                    db.commit();
                    Session::setBalance(newEurBalance);
                    return true;
                }
            }
        }
        //return true;
    }
}

bool QueryEngine::lockCard() {
    QSqlQuery query;
    query.exec("UPDATE card SET locked = 1 WHERE card_id = " + QString::number(Session::getSessionCardID()) + ";");
    if(query.numRowsAffected() > 0) {
        qDebug() << "Card locked";
        return true;
    } else {
        qDebug() << "Locking card failed";
        return false;
    }
}


bool QueryEngine::isCardLocked() {
    QSqlQuery query;
    query.exec("SELECT locked FROM card WHERE card_id = " + QString::number(Session::getSessionCardID()) + ";");
    query.first();
    int test = query.value(0).toUInt();
    if(test) {
        return true;
    } else {
        return false;
    }
}
