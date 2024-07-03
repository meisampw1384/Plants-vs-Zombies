#include "log_in.h"
#include "ui_log_in.h"
#include "restore_pass.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QMessageBox>
#include <QTcpSocket>
#include <QDebug>

log_in::log_in(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::log_in)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);

    // Connect the readyRead signal to the readResponse slot
    connect(socket, &QTcpSocket::readyRead, this, &log_in::readResponse);
}

log_in::~log_in()
{
    delete ui;
}

void log_in::on_buttonBox_rejected()
{
    // Handle rejection if needed
}

void log_in::on_buttonBox_accepted()
{
    QString username = ui->line_edit_name->text();
    QString password = ui->line_edit_password->text();

    QJsonObject request;
    request["action"] = "login";
    request["username"] = username;
    request["password"] = password;

    QJsonDocument doc(request);
    QByteArray data = doc.toJson();

    socket->connectToHost("127.0.0.1", 1234);

    if (socket->waitForConnected(5000)) {
        qDebug() << "Connection established";

        // Ensure the data is written to the server
        socket->write(data);
        socket->flush();


        // Wait for the response
        if (!socket->waitForReadyRead(5000)) {
            qDebug() << "No response from server";
            QMessageBox::warning(this, "Error", "No response from the server.");
        }
    } else {
        qDebug() << "Failed to connect to server";
        QMessageBox::warning(this, "Error", "Failed to connect to the server.");
    }
}

void log_in::on_pushButton_clicked()
{
    restore_pass *RP = new restore_pass();
    RP->show();
}

void log_in::readResponse()
{
    QByteArray response = socket->readAll();
    qDebug() << "Received response:" << response;  // Debug output
    QJsonDocument doc = QJsonDocument::fromJson(response);
    QJsonObject obj = doc.object();

    if (obj["result"].toString() == "success") {
        QMessageBox::information(this, "Login Success", "Login successful!");
        accept();
    } else {
        QMessageBox::warning(this, "Login Failed", "Invalid username or password!");
        reject();
    }

    // Disconnect the socket
    socket->disconnectFromHost();
}

