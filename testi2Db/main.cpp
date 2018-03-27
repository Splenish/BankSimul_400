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

    return a.exec();
}
