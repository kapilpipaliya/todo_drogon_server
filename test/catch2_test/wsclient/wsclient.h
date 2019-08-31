#ifndef WSCLIENT_H
#define WSCLIENT_H

#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>
#include <QtNetwork/QSslError>
#include <QtCore/QList>
#include <QtCore/QString>
#include <QtCore/QUrl>

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QProcess>
#include <QTimer>
#include <functional>

#include "json.hpp"
using nlohmann:: json;

class SslEchoClient : public QObject
{
    Q_OBJECT
    static short int PING_INTERVAL;
    static short int PING_INTERVAL_COUNT_MAX;

public:
    explicit SslEchoClient(const QUrl &url, QObject *parent = nullptr);
    void sendMessage(QString message);
    bool bind(const nlohmann::json &event, std::function<void(json)> callback);
    bool unbind(const nlohmann::json &event);

    QWebSocket m_webSocket;

private Q_SLOTS:
    void onConnected();
    void onTextMessageReceived(QString message);
    void onSslErrors(const QList<QSslError> &errors);

private:
    QUrl url;

    QTimer *ping_timer;
    //QNetworkReply *reply = nullptr;
    //QNetworkAccessManager qnam;

    short int intervals_from_last_pong;

    std::map<std::string, std::function<void(json)>> callbacks;

    void reconnect();

    json jsonparse(std::string msg);
    void dispatch(nlohmann::json event, json data);
};

class WsInst {
public:
    WsInst();
    static SslEchoClient &getClient();
};



#endif // WSCLIENT_H
