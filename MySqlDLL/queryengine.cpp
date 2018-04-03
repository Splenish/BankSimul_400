#include "queryengine.h"

QueryEngine::QueryEngine()
{
    newSession = new Session;
}

void QueryEngine::connectToDatabase() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("mysli.oamk.fi");
    db.setDatabaseName("opisk_t5raki00");
    db.setUserName("t5raki00");
    db.setPassword("DmZne33hza4ygc7C");
    bool ok = db.open();
    qDebug() << ok;
}

bool QueryEngine::getAccountID(QString card_number) {
    QSqlQuery query;
    query.exec("SELECT card_id FROM card WHERE card_number = \"" + card_number + "\";");
    query.first();
    newSession->setSessionCardID(query.value(0).toInt());
    QString card_id = query.value(0).toString();
    query.exec("SELECT account_id from card where card_id = " + card_id + ";");
    query.first();
    int account_id = query.value(0).toInt();

    if(query.size() > 0) {

        newSession->setSessionAccountID(account_id);
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
    qDebug() << "cardID:" << newSession->getSessionCardID();
    query.exec("SELECT card_id FROM card WHERE pincode = \""
               + pincode + "\" AND card_id = " + QString::number(newSession->getSessionCardID()) + ";");
    if(query.size() > 0) {
        qDebug() << "oikea tunnus";
        return true;
    } else {
        qDebug() << "väärä tunnus";
        return false;
    }
}
