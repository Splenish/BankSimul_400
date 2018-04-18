#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>
#include <QTimer>
#include "mysqldll.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_quitButton_clicked();

    void on_Euros_textEdited(const QString &arg1);

    void on_Coins_textEdited(const QString &arg1);

    void updateCurrency();

    void on_showTransactionsButton_clicked();

    void on_edellinenButton_clicked();

    void on_seuraavaButton_clicked();

private:
    Ui::MainWindow *ui;
    MySqlDLL *DLLobject;
    QTimer *timer;
    int pagecount = 0;
    QStringList transactions;
};

#endif // MAINWINDOW_H
