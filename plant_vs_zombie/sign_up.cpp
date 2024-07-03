#include "sign_up.h"
#include "menu.h"
#include "ui_sign_up.h"
#include <QJsonObject>
#include <QFile>
#include <QJsonArray>
#include <QMessageBox>
#include <QJsonDocument>

sign_up::sign_up(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sign_up)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);

    connect(socket,&QTcpSocket::readyRead,this,&sign_up::readyResponse);
}

sign_up::~sign_up()
{
    delete ui;
}

void sign_up::on_buttonBox_rejected()
{

}


void sign_up::on_buttonBox_accepted()
{
    QString name = this->ui->line_edit_name_2->text();
    QString username = this->ui->line_edit_username_2->text();
    QString phoneNumber = this->ui->line_edit_phonenumber_2->text();
    QString email = this->ui->line_edit_email_2->text();
    QString password = this->ui->line_edit_password_2->text();

    QJsonObject request;
    request["action"]="signup";
    request["username"]=username;
    request["phoneNumber"]=phoneNumber;
    request["email"]=email;
    request["name"]=name;
    request["password"]=password;

    QJsonDocument doc(request);
    QByteArray data= doc.toJson();

    socket->connectToHost("127.0.0.1",1234);
    if (socket->waitForConnected(5000)){
        qDebug()<<"connection established";

        socket->write(data);
        socket->flush();

        if (!socket->waitForReadyRead(5000)){
            qDebug()<<"No response from server";
            QMessageBox::warning(this, "Error", "No response from the server.");

        }
    }
    else {
        qDebug() << "Failed to connect to server";
        QMessageBox::warning(this, "Error", "Failed to connect to the server.");

    }
}


void sign_up::readyResponse()
{
    QByteArray response= socket->readAll();
    qDebug()<<"Received response:"<<response;
    QJsonDocument doc = QJsonDocument::fromJson(response);
    QJsonObject obj=doc.object();

    if (obj["result"].toString()=="success"){
        QMessageBox::information(this, "SignUp Success", "SignUp Successfully!");
        accept();
    }
    else {
        QMessageBox::warning(this, "Failed SignUp", "Invalid informations!");
        reject();
    }
}
