#include "restore_pass.h"
#include "ui_restore_pass.h"
#include <QJsonObject>
#include <QFile>
#include <QJsonArray>
#include <QMessageBox>
#include <QJsonValue>
#include <QJsonDocument>

restore_pass::restore_pass(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::restore_pass)
{
    ui->setupUi(this);
    socket=new QTcpSocket(this);
    connect(socket,&QTcpSocket::readyRead,this,&restore_pass::readyResponse);
}

restore_pass::~restore_pass()
{
    delete ui;
}

void restore_pass::on_buttonBox_accepted()
{
    QString phone_number=this->ui->line_edit_phone->text();
    QString new_password=this->ui->lineEdit_password->text();
    QJsonObject request;
    request["action"]="restore";
    request["phoneNumber"]=phone_number;
    request["newPassword"]=new_password;

    QJsonDocument doc(request);
    QByteArray data = doc.toJson();
    socket->connectToHost("127.0.0.1",1234);

    if (socket->waitForConnected(5000)){
        qDebug()<<"Connection established!";

        socket->write(data);
        socket->flush();

        if (!socket->waitForReadyRead(5000)){
            qDebug()<<"No response from server";
            QMessageBox::warning(this,"Erorr","No response from server.");
        }

    }
}

void restore_pass::readyResponse()
{
    QByteArray response = socket->readAll();
    qDebug() << "Received response:" << response;  // Debug output
    QJsonDocument doc = QJsonDocument::fromJson(response);
    QJsonObject obj = doc.object();

    if (obj["result"].toString() == "success") {
        QMessageBox::information(this, "Password Changed", "Password changed successfully!");
        this->accept();
    }
    else {
        QMessageBox::warning(this, "Error", "Phone number not found. Please check and try again.");
    }
}

