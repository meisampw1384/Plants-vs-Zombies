#include "restore_pass.h"
#include "ui_restore_pass.h"
#include <QJsonObject>
#include <QFile>
#include <QJsonArray>
#include <QMessageBox>
#include <QJsonValue>
#include <QCryptographicHash>
#include <QJsonDocument>
#include <QCryptographicHash>

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

    QRegularExpression password_re("^^(?=.*[A-Za-z])(?=.*\\d)[A-Za-z\\d]{8,}$");
    if (!password_re.match(new_password).hasMatch()) {
        QMessageBox::warning(this, "Error", "password should have at least 8 characters, including at least one letter and one number.!");
        reject();
        return;
    }

    QByteArray hash = QCryptographicHash::hash(new_password.toUtf8(), QCryptographicHash::Sha256);
    QString password = QString(hash.toHex());

    QJsonObject request;
    request["action"]="restore";
    request["phoneNumber"]=phone_number;
    request["newPassword"]=password;

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

