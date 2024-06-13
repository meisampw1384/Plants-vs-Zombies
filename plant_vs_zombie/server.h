#ifndef SERVER_H
#define SERVER_H
#include <QTcpSocket>
#include <QTcpServer>

#include <QObject>

class Server : public QTcpServer
{
    Q_OBJECT


public:
    Server(QObject *parent=nullptr);
    void startServer();

private slots:
    void new_connection();
    void ReadyRead();
    void ClientDisconnected();
private:
    void processReq(const QJsonObject &request, QTcpSocket *socket);
    QJsonDocument readJsonFile(const QString &filePath);
    void writeJsonFile(const QString &filePath,const QJsonDocument &doc);

    QList<QTcpSocket*> clients;
};

#endif // SERVER_H
