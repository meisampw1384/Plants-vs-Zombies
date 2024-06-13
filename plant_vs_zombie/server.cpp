#include "server.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QDebug>

Server::Server(QObject *parent): QTcpServer(parent)
{

}

void Server::startServer()
{
    if (listen(QHostAddress::Any,1234)){
        connect(this,&Server::newConnection,this,&Server::new_connection);
        qDebug()<<"Server started on port 1234";
    }
    else{
        qDebug()<<"Server failed to start";
    }
}

void Server::new_connection()
{
    QTcpSocket *socket=nextPendingConnection();
    clients.append(socket);
    connect(socket,&QTcpSocket::readyRead,this,&Server::ReadyRead);
}

void Server::ReadyRead()
{
    QTcpSocket *socket=qobject_cast<QTcpSocket *>(sender());
    if (!socket)return;

    QByteArray data=socket->readAll();
    QJsonDocument doc=QJsonDocument::fromJson(data);
    QJsonObject request=doc.object();

    processReq(request,socket);
}

void Server::ClientDisconnected()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());

    if (!socket)return;
    clients.removeOne(socket);
    socket->deleteLater();

    qDebug()<<"Client disconnected"<<socket->peerAddress().toString();
}

void Server::processReq(const QJsonObject &request, QTcpSocket *socket)
{
    QString action=request["action"].toString();
    QJsonObject response;
    if (action == "login") {
        QString username = request["username"].toString();
        QString password = request["password"].toString();

        QJsonDocument doc = readJsonFile("information.json");
        QJsonArray jsonArray = doc.array();
        bool success = false;

        for (const QJsonValue &value : jsonArray) {
            QJsonObject obj = value.toObject();
            if (obj["username"].toString() == username && obj["password"].toString() == password) {
                success = true;
                break;
            }
        }
        response["result"]=success?"success" : "failure";
    }
    else if (action=="signup"){
        QJsonObject newUser;
        newUser["name"] = request["name"].toString();
        newUser["username"] = request["username"].toString();
        newUser["phoneNumber"] = request["phoneNumber"].toString();
        newUser["email"] = request["email"].toString();
        newUser["password"] = request["password"].toString();

        QJsonDocument doc=readJsonFile("information.json");
        QJsonArray jsonArray=doc.array();
        jsonArray.append(newUser);

        writeJsonFile("information.json",QJsonDocument(jsonArray));
        response["result"]="success";

    }
    else if (action=="restore"){
        QString phoneNumber = request["phoneNumber"].toString();
        QString newPassword = request["newPassword"].toString();

        QJsonDocument doc = readJsonFile("information.json");
        QJsonArray jsonArray = doc.array();
        bool success = false;

        for (int i = 0; i < jsonArray.size(); ++i) {
            QJsonObject obj = jsonArray[i].toObject();
            if (obj["phoneNumber"].toString() == phoneNumber) {
                obj["password"] = newPassword;
                jsonArray[i] = obj;
                success = true;
                break;
            }
        }
        if (success){
            writeJsonFile("information.json",QJsonDocument(jsonArray));
        }
        response["result"]= success ? "success" : "failure";
    }
    QJsonDocument responseDoc(response);
    socket->write(responseDoc.toJson());
    socket->disconnectFromHost();
}

QJsonDocument Server::readJsonFile(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Could not open file for reading";
        return QJsonDocument();
    }

    QByteArray data = file.readAll();
    file.close();

    return QJsonDocument::fromJson(data);
}

void Server::writeJsonFile(const QString &filePath, const QJsonDocument &doc)
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Could not open file for writing";
        return;
    }

    file.write(doc.toJson());
    file.close();
}

