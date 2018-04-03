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
    }

}

MainWindow::~MainWindow()
{
    delete ui;
    delete DLLobject;
    DLLobject = 0;
}
