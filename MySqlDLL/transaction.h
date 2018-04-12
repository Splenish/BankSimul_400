#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QtSql>
#include <QString>
#include <QDebug>
#include <QStringList>
#include <QVector>
#include "session.h"

class Transaction
{
public:
    Transaction();
    QStringList lastTransactions();
    QStringList lastTransactions(int page);
private:
    //QStringList transactions;
    //QList<QStringList> transactions;
    //QStringList transactionData;
    int transactionColumns = 3;
    int balanceCheckAmount = 5;
    int transactionCheckAmount = 10;
    //QStringList tilitapahtumat;
};

#endif // TRANSACTION_H
