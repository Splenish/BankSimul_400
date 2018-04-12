#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    DLLobject = new MySqlDLL;
    DLLobject->databaseConnect();
    if(DLLobject->validateCard("testcard1")) {
        DLLobject->validatePincode("1234");
        qDebug() << DLLobject->getUserData("first_name");
        qDebug() << DLLobject->getUserData("last_name");
    }
    //qDebug() << DLLobject->getSessionBalance();
    //DLLobject->withdrawalEvent(5000);
    //QStringList transactionList = DLLobject->getTransactions();
    /*for(int i = 0; i < transactionList.size(); i++) {
        qDebug() << transactionList[i];
    }*/
    //qDebug() << "tän pitäs olla xrp kurssi: " << DLLobject->getCoinValue("xrp");
    qDebug() << "btc ja xrp balance " << DLLobject->getUserCoinBalance("btc") << " " << DLLobject->getUserCoinBalance("xrp");
    qDebug() << "ota mut ja lähetää vittuu";
    DLLobject->buyCryptoWithEurEvent("xrp", 20);
    DLLobject->disconnect();

}

MainWindow::~MainWindow()
{
    delete ui;
    delete DLLobject;
    DLLobject = 0;
}
