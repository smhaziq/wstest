#ifndef BATCH_CONNECT_H
#define BATCH_CONNECT_H
#include <QList>
#include <QWebSocket>
class BatchConnect : public QObject {
    Q_OBJECT

  public:
    BatchConnect(const QString& server_url, int conection_count,
                 bool ignore_ssl_errors, QObject* parent = nullptr);
    void StartConnections();

    void CloseConnections();

    ~BatchConnect();

  private:
    void PrintSummary();

    QString server_url_;
    int connection_count_;
    bool ignore_ssl_errors_;
    int connected_count_;
    int disconnected_count_;
    QList<std::shared_ptr<QWebSocket>> connections_;
};
#endif
