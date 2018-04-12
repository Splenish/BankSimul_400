#include "transaction.h"

Transaction::Transaction()
{

}

QStringList Transaction::lastTransactions() {
    QStringList tilitapahtumat;
    QSqlQuery query;
    query.exec("SELECT DATE_FORMAT(date, '%d.%m.%Y'), amount, type FROM transaction WHERE account_id = "
               + QString::number(Session::getSessionAccountID()) + ";");
    query.last();
    for(int i = 0; i < balanceCheckAmount; i++) {
        QString tapahtumaData;
        for(int j = 0; j < transactionColumns; j++) {
            tapahtumaData = tapahtumaData + query.value(j).toString() + " ";
        }
        tilitapahtumat << tapahtumaData;
        if(!query.previous()) {
            qDebug() << "no more data";
            break;
        }
    }
    return tilitapahtumat;
}

QStringList Transaction::lastTransactions(int page) {
    QStringList tilitapahtumat;
    QSqlQuery query;
    query.exec("SELECT DATE_FORMAT(date, '%d.%m.%Y'), amount, type FROM transaction WHERE account_id = "
               + QString::number(Session::getSessionAccountID()) + ";");
    qDebug() << "size:" << query.size();
    int index = query.size() - page*10;
    query.seek(index-1);

    for(int i = 0; i < transactionCheckAmount; i++) {
        QString tapahtumaData;
        for(int j = 0; j < transactionColumns; j++) {
            tapahtumaData = tapahtumaData + query.value(j).toString() + " ";
        }
        tilitapahtumat << tapahtumaData;
        if(!query.previous()) {
            qDebug() << "no more data";
            break;
        }
    }
    return tilitapahtumat;
}
