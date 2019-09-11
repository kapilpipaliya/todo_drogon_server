#ifndef WSCLIENT_H
#define WSCLIENT_H

#include <QtCore/QList>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QUrl>
#include <QtNetwork/QSslError>
#include <QtWebSockets/QWebSocket>

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QProcess>
#include <QTimer>
#include <functional>

#include "json.hpp"

class SslEchoClient : public QObject {
  Q_OBJECT

 public:
  explicit SslEchoClient(const QUrl &url, QObject *parent = nullptr);
  void sendMessage(QString message);
  bool bind(const nlohmann::json &event,
            std::function<void(nlohmann::json)> callback);
  bool bindOnce(const nlohmann::json &event,
                std::function<void(nlohmann::json)> callback);
  bool unbind(const nlohmann::json &event);
  QWebSocket &getWebSocket() { return m_webSocket; }

 private Q_SLOTS:
  void onConnected();
  void onTextMessageReceived(QString message);
  void onSslErrors(const QList<QSslError> &errors);

 private:
  template <typename T>
  void bindOnce(T arg1, std::function<void(nlohmann::json)> callback);
  static short int PING_INTERVAL;
  static short int PING_INTERVAL_COUNT_MAX;

  QWebSocket m_webSocket;

  QUrl url;

  QTimer *ping_timer;
  // QNetworkReply *reply = nullptr;
  // QNetworkAccessManager qnam;

  short int intervals_from_last_pong;

  std::map<std::string, std::tuple<int, std::function<void(nlohmann::json)>>>
      callbacks;

  void reconnect();

  nlohmann::json jsonparse(std::string msg);
  void dispatch(nlohmann::json event, nlohmann::json data);
};

class WsInst {
 public:
  WsInst();
  static SslEchoClient &getClient();
};

#endif  // WSCLIENT_H
