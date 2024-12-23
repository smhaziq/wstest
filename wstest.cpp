#include <QCommandLineParser>
#include <QCoreApplication>

#include "batch_connect.h"

int main(int argc, char* argv[]) {
    QCoreApplication app(argc, argv);

    QCommandLineParser parser;
    parser.setApplicationDescription("WebSocket Tester");
    parser.addHelpOption();

    QCommandLineOption server_option(QStringList() << "s"
                                                   << "server",
                                     "WebSocket server URL to connect to.",
                                     "server");
    parser.addOption(server_option);

    QCommandLineOption connections_option(
        QStringList() << "n"
                      << "connections",
        "Number of WebSocket connections to create.", "connections");
    parser.addOption(connections_option);

    QCommandLineOption ignore_ssl_option(QStringList() << "i"
                                                       << "ignore-ssl-errors",
                                         "Ignore SSL errors.");
    parser.addOption(ignore_ssl_option);

    parser.process(app);

    QString server_url = parser.value(server_option);
    int conection_count = parser.value(connections_option).toInt();
    bool ignore_ssl_errors = parser.isSet(ignore_ssl_option);
    if (server_url.isEmpty() || conection_count <= 0) {
        qWarning() << "Invalid arguments. Use --help for usage.";
        return -1;
    }

    BatchConnect tester(server_url, conection_count, ignore_ssl_errors);
    tester.StartConnections();

    QObject::connect(&app, &QCoreApplication::aboutToQuit,
                     [&tester]() { tester.CloseConnections(); });

    return app.exec();
}
