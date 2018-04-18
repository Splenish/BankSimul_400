#include "cryptocurrency.h"

float Cryptocurrency::btcCourse = 0;
float Cryptocurrency::ethCourse = 0;
float Cryptocurrency::xrpCourse = 0;
float Cryptocurrency::bchCourse = 0;
float Cryptocurrency::ltcCourse = 0;

Cryptocurrency::Cryptocurrency()
{
    manager = new QNetworkAccessManager();
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(managerFinished(QNetworkReply*)));
    connect(this, &Cryptocurrency::replyFinished, &loop, &QEventLoop::quit);
    request.setAttribute(QNetworkRequest::FollowRedirectsAttribute, QNetworkRequest::RedirectionTargetAttribute);
}

void Cryptocurrency::setCoin(QString coin) {
    if(coin == "btc") {
        request.setUrl(QUrl("https://api.coinmarketcap.com/v1/ticker/bitcoin/?convert=EUR"));
    } else if (coin == "eth") {
        request.setUrl(QUrl("https://api.coinmarketcap.com/v1/ticker/ethereum/?convert=EUR"));
    } else if (coin == "xrp") {
        request.setUrl(QUrl("https://api.coinmarketcap.com/v1/ticker/ripple/?convert=EUR"));
    } else if (coin == "bch") {
        request.setUrl(QUrl("https://api.coinmarketcap.com/v1/ticker/bitcoin-cash/?convert=EUR"));
    } else if (coin == "ltc") {
        request.setUrl(QUrl("https://api.coinmarketcap.com/v1/ticker/litecoin/?convert=EUR"));
    } else {
        qDebug() << "invalid coin";
    }
    manager->get(request);
    loop.exec();
}

void Cryptocurrency::managerFinished(QNetworkReply *reply) {
    emit replyFinished();
    if(reply->error()) {
        //qDebug() << reply->errorString();
        return;
    }


    QString json_string;
    json_string = reply->readAll();
    //qDebug() << json_string;
    json_string.remove("[");
    json_string.remove("]");
    QJsonParseError error_json;
    QJsonDocument json_doc = QJsonDocument::fromJson(json_string.toUtf8(), &error_json);
    if(json_doc.isNull()) {
        qDebug() << "failed to create json doc";
        qDebug() << error_json.errorString();
        qDebug() << json_string;
        //getRequest();
    }

    if(!json_doc.isObject()) {
        qDebug() << "not an object";
    }

    QJsonObject json_obj = json_doc.object();
    //QJsonObject ticker = json_obj["ticker"].toObject();
    //QString priceStr = ticker["price"].toString();
    QString priceStr = json_obj["price_eur"].toString();
    double price = priceStr.toFloat();
    //setCourse(ticker["base"].toString(), price);
    setCourse(json_obj["symbol"].toString(), price);
}

void Cryptocurrency::setCourse(QString coin, float course) {
    if(coin == "BTC") {
        btcCourse = course;
    } else if (coin == "ETH") {
        ethCourse = course;
    } else if (coin == "XRP") {
        xrpCourse = course;
    } else if (coin == "BCH") {
        bchCourse = course;
    } else if (coin == "LTC") {
        ltcCourse = course;
    } else {
        qDebug() << "invalid coin";
    }
}

float Cryptocurrency::getCourse(QString coin) {
    if(coin == "btc") {
        return btcCourse;
    } else if (coin == "eth") {
        return ethCourse;
    } else if (coin == "xrp") {
        return xrpCourse;
    } else if (coin == "bch") {
        return bchCourse;
    } else if (coin == "ltc") {
        return ltcCourse;
    } else {
        return -1;
    }
}
