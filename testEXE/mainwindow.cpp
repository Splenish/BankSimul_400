#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    DLLobject = new MySqlDLL;
    DLLobject->databaseConnect();
    if(DLLobject->validateCard("0B0032AD79")) {
        DLLobject->validatePincode("1234");
        qDebug() << DLLobject->getUserData("first_name");
        qDebug() << DLLobject->getUserData("last_name");
    }
    //qDebug() << DLLobject->getSessionBalance();
    //DLLobject->withdrawalEvent(20);
    //QStringList transactionList = DLLobject->getTransactions();
    /*for(int i = 0; i < transactionList.size(); i++) {
        qDebug() << transactionList[i];
    }*/
    //qDebug() << "tän pitäs olla xrp kurssi: " << DLLobject->getCoinValue("xrp");
    //qDebug() << "btc ja xrp balance " << DLLobject->getUserCoinBalance("btc") << " " << DLLobject->getUserCoinBalance("xrp");
    //qDebug() << "ota mut ja lähetää vittuu";
    //DLLobject->sellCryptoEvent("bch", 50);


    qDebug() << DLLobject->getCoinValue("btc");
    //qDebug() << "is card locked" << DLLobject->isCardLocked();
    //qDebug() << "lock card" << DLLobject->lockCard();
    //qDebug() << "is card locked" << DLLobject->isCardLocked();
    //DLLobject->buyCryptoEvent("xrp", 1);
    ui->btcKurssiValue->setText(QString::number(DLLobject->getCoinValue("btc")));
    /*timer = new QTimer;
    timer->setInterval(30);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateCurrency);
    timer->start();*/
    //DLLobject->buyCryptoEvent("eth", 20);
    //DLLobject->sellCryptoEvent("bch", 3);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete DLLobject;
    DLLobject = 0;
}
void MainWindow::on_quitButton_clicked()
{
    DLLobject->disconnect();
    close();
}

void MainWindow::on_Euros_textEdited(const QString &arg1)
{
    float eurot = arg1.toFloat();
    float coinVaulue = DLLobject->getCoinValue("btc");
    float coinAmount = eurot / coinVaulue;
    ui->Coins->setText(QString::number(coinAmount));
}

void MainWindow::on_Coins_textEdited(const QString &arg1)
{
    float coins = arg1.toFloat();
    float coinValue = DLLobject->getCoinValue("btc");
    float eurAmount = coins * coinValue;
    ui->Euros->setText(QString::number(eurAmount));
}

void MainWindow::updateCurrency() {
    ui->btcKurssiValue->setText(QString::number(DLLobject->getCoinValue("btc")));
}

void MainWindow::on_showTransactionsButton_clicked()
{
    ui->transactionList->clear();
    transactions = DLLobject->getTransactions(pagecount);
    for(int i = 0; i < transactions.length(); i++) {
        ui->transactionList->addItem(transactions[i]);
    }
}

void MainWindow::on_edellinenButton_clicked()
{

    if(!(transactions.length() < 10)) {
        pagecount++;
        ui->transactionList->clear();
        transactions = DLLobject->getTransactions(pagecount);
        qDebug() << pagecount;
        for(int i = 0; i < transactions.length(); i++) {
            ui->transactionList->addItem(transactions[i]);
        }
    }


}

void MainWindow::on_seuraavaButton_clicked()
{
    if(!(pagecount == 0)) {
        pagecount--;
        ui->transactionList->clear();
        transactions = DLLobject->getTransactions(pagecount);
        qDebug() << pagecount;
        for(int i = 0; i < transactions.length(); i++) {
            ui->transactionList->addItem(transactions[i]);
        }
    }
}
