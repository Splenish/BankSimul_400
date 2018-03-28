#include "mainwindow.h"
#include <QApplication>
#include <QtSql>
#include <QDebug>
#include <QSqlDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("mysli.oamk.fi");
    db.setDatabaseName("opisk_t5raki00");
    db.setUserName("t5raki00");
    db.setPassword("DmZne33hza4ygc7C");
    bool ok = db.open();
    qDebug() << "testi";
    qDebug() << ok;
    if(ok) {
        qDebug() << "jes";
    } else if(!ok) {
        qDebug() << "perse";
        qDebug() << db.lastError().number();
        qDebug() <<  db.isValid();
    }
    QSqlQuery query;
    qDebug() << query.exec("SELECT * FROM asiakas");

    /*
    while(query.next()) {
        int id = query.value(0).toInt();
        QString etunimi = query.value(1).toString();
        QString sukunimi = query.value(2).toString();
        qDebug() << id << etunimi << sukunimi;
    }*/
    query.last();
    for(int i = 0; i < 3; i++) {
        int id = query.value(0).toInt();
        QString etunimi = query.value(1).toString();
        QString sukunimi = query.value(2).toString();
        qDebug() << id << etunimi << sukunimi;
        query.previous();
    }

    return a.exec();
}
