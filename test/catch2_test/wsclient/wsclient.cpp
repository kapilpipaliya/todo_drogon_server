#include "wsclient.h"

#include <QtCore/QDebug>
#include <QtWebSockets/QWebSocket>
#include <QCoreApplication>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include "once.h"
#include "spdlogfix.h"

short int SslEchoClient::PING_INTERVAL = 5000;
short int SslEchoClient::PING_INTERVAL_COUNT_MAX = 3;

SslEchoClient::SslEchoClient(const QUrl &url, QObject *parent) :
    QObject(parent),
    url(url),
    ping_timer(new QTimer(this)),
    intervals_from_last_pong(0)
{
    connect(ping_timer, &QTimer::timeout, [=, this]{
        if(intervals_from_last_pong >= PING_INTERVAL_COUNT_MAX){
            SPDLOG_TRACE("Connection lost. ( no pongs )");
            reconnect();
        } else {
            m_webSocket.ping();

            ++intervals_from_last_pong;
        }
    });
    ping_timer->setInterval(PING_INTERVAL);


    connect(&m_webSocket, &QWebSocket::connected, this, &SslEchoClient::onConnected);
    connect(&m_webSocket, QOverload<const QList<QSslError>&>::of(&QWebSocket::sslErrors),
            this, &SslEchoClient::onSslErrors);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &SslEchoClient::reconnect);
    connect(&m_webSocket, &QWebSocket::pong, this, [=, this] {
        intervals_from_last_pong = 0;
    });
    reconnect();
}
void SslEchoClient::onConnected()
{
    SPDLOG_TRACE("WebSocket connected");

    ping_timer->start();

    connect(&m_webSocket, &QWebSocket::textMessageReceived,
            this, &SslEchoClient::onTextMessageReceived, Qt::UniqueConnection);

    //m_webSocket.sendTextMessage(QStringLiteral("Hello, world!"));
}

void SslEchoClient::onSslErrors(const QList<QSslError> &errors)
{
    Q_UNUSED(errors)
    SPDLOG_TRACE("SslEchoClient::onSslErrors()");
    SPDLOG_TRACE(m_webSocket.errorString().toStdString());

    // WARNING: Never ignore SSL errors in production code.
    // The proper way to handle self-signed certificates is to add a custom root
    // to the CA store.

    m_webSocket.ignoreSslErrors();
}
void SslEchoClient::reconnect()
{
    ping_timer->stop();

    SPDLOG_TRACE("QSlackJukebox::reconnect()");
    m_webSocket.open(url);
}

json SslEchoClient::jsonparse(std::string msg)
{
    try
    {
        auto j =json::parse(msg);
        return j;
    }
    catch ([[maybe_unused]] json::parse_error& e)
    {
       //SPDLOG_TRACE("message: {}", e.what());
       //SPDLOG_TRACE("exception id: {}", e.id);
       //SPDLOG_TRACE("byte position of error:", e.byte);
        throw ("Json can not be parsed");
    }
}

void SslEchoClient::dispatch(json event, nlohmann::json data)
{

    auto search = callbacks.find(event.dump());
    if (search != callbacks.end()) {
       //Found
        search->second(data);
    } else {
        SPDLOG_TRACE("Not found");
    }
}
void SslEchoClient::sendMessage(QString message)
{
//    m_webSocket.state()
    switch (m_webSocket.state()) {
    case QAbstractSocket::HostLookupState:
    case QAbstractSocket::ConnectingState:
    case QAbstractSocket::BoundState: // ?
        //when open send message;
        //connect(&m_webSocket, &QWebSocket::connected, this, [this, &message](){ m_webSocket.sendTextMessage(message); });
        Once::connect(&m_webSocket, &QWebSocket::connected,
              [this, message](){ m_webSocket.sendTextMessage(message); });
        break;
    case QAbstractSocket::ConnectedState:
        m_webSocket.sendTextMessage(message);
        break;
    case QAbstractSocket::UnconnectedState:
    case QAbstractSocket::ClosingState:
        reconnect();
        // when open send message..
        Once::connect(&m_webSocket, &QWebSocket::connected,
              [this, &message](){ m_webSocket.sendTextMessage(message); });
        break;
    default:
        break;
    }

//    message = QString::fromStdString( QJsonDocument ( QJsonObject (
//                {
//                    { "id"      ,    ++last_message_id   },
//                    { "type"    ,    "message"           },
//                    { "text"    ,    message             }
//                }
//           )
//       ).toJson().toStdString()
//   );

   SPDLOG_TRACE("SslEchoClient::sendMessage");
   SPDLOG_TRACE("  ", message.toStdString());
}

bool SslEchoClient::bind(const json &event, std::function<void (nlohmann::json)> callback)
{
    auto r = callbacks.insert({event.dump(), callback});
    return r.second;
}

bool SslEchoClient::unbind(const json &event)
{
  auto removed_elements = callbacks.erase(event.dump());
  if(removed_elements>0){
      return true;
  }
  return false;
}


void SslEchoClient::onTextMessageReceived(QString message)
{
    SPDLOG_TRACE("Message received: ", message.toStdString());

    SPDLOG_TRACE(message.toStdString());

    //QJsonObject _message(QJsonDocument::fromJson(QByteArray::fromStdString(message.toStdString()) , new QJsonParseError()).object());
    auto _message = jsonparse(message.toStdString());

    if(_message.is_array()){
        for (auto &et: _message) {
            auto event = et[0];
            auto message = et;
            message.erase(0);
            dispatch(event, message);
        }
    }

}


WsInst::WsInst()
{
}

SslEchoClient &WsInst::getClient()
{
    static auto wsclient = SslEchoClient(QUrl(QStringLiteral("wss://localhost:8401/madmin")));
    return wsclient;
}
