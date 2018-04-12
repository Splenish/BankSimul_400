#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    manager = new QNetworkAccessManager();
    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(managerFinished(QNetworkReply*)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete manager;
}

void MainWindow::managerFinished(QNetworkReply *reply) {
    if(reply->error()) {
        qDebug() << reply->error();
        return;
    }

    QString answer = reply->readAll();

    qDebug() << answer;
}


void MainWindow::on_pushButton_clicked()
{
    request.setUrl(QUrl("https://api.coinmarketcap.com/v1/ticker/bitcoin/"));
    manager->get(request);
}
