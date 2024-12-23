#include "batch_connect.h"

BatchConnect::BatchConnect(const QString& server_url, int conection_count,
                           bool ignore_ssl_errors, QObject* parent)
    : QObject(parent),
      server_url_(server_url),
      connection_count_(conection_count),
      ignore_ssl_errors_(ignore_ssl_errors),
      connected_count_(0),
      disconnected_count_(0) {}

void BatchConnect::StartConnections() {
    for (int i = 0; i < connection_count_; ++i) {
        const auto& socket = std::make_shared<QWebSocket>();
        connections_.append(socket);

        if (ignore_ssl_errors_) {
            connect(socket.get(), &QWebSocket::sslErrors, this,
                    [=](const QList<QSslError>& errors) {
                        Q_UNUSED(errors);
                        socket->ignoreSslErrors();
                    });
        }

        connect(socket.get(), &QWebSocket::connected, this, [=]() {
            ++connected_count_;
            PrintSummary();
        });
        connect(socket.get(), &QWebSocket::disconnected, this, [=]() {
            ++disconnected_count_;
            PrintSummary();
        });
        connect(socket.get(), &QWebSocket::errorOccurred, this,
                [=](QAbstractSocket::SocketError error) {
                    qDebug() << socket->errorString();
                });

        socket->open(QUrl(server_url_));
    }
}

void BatchConnect::CloseConnections() {
    for (const auto& socket : qAsConst(connections_)) {
        if (socket->isValid()) {
            socket->close();
        }
        socket->deleteLater();
    }
    connections_.clear();
}

BatchConnect::~BatchConnect() { CloseConnections(); }

void BatchConnect::PrintSummary() {
    int waiting_count =
        connection_count_ - (connected_count_ + disconnected_count_);
    qDebug() << "Summary: Connected:" << connected_count_
             << "Disconnected:" << disconnected_count_
             << "Waiting:" << waiting_count;
}
