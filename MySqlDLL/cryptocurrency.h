#ifndef CRYPTOCURRENCY_H
#define CRYPTOCURRENCY_H

#include <QObject>
#include <QVariant>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QUrl>
#include <QEventLoop>

class Cryptocurrency : public QObject
{
    Q_OBJECT
public:
    Cryptocurrency();
    void setCoin(QString coin);
    static void setCourse(QString coin, float course);
    static float getCourse(QString coin);

private:
    QNetworkAccessManager *manager;
    QNetworkRequest request;
    QEventLoop loop;
    static float btcCourse;
    static float ethCourse;
    static float xrpCourse;
    static float bchCourse;
    static float ltcCourse;
private slots:
    void managerFinished(QNetworkReply *reply);
signals:
    void replyFinished();
};

#endif // CRYPTOCURRENCY_H
