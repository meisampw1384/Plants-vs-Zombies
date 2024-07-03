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

    if(name.size() < 3)
    {
        QMessageBox::warning(this, "Error", "name should have at least 3 characters");
        reject();
        return;
    }

    QRegularExpression phoneNumber_re("^0\\d{10}$");
    if (!phoneNumber_re.match(phoneNumber).hasMatch()) {
        QMessageBox::warning(this, "Error", "phone number should have 11 digits and starts with 0 !");
        reject();
        return;
    }

    QRegularExpression username_re("^[a-zA-Z0-9_]{8,}$");
    if (!username_re.match(username).hasMatch()) {
        QMessageBox::warning(this, "Error", "username must have at least 8 characters");
        reject();
        return;
    }
    QRegularExpression email_re("^[\\w\\.]+@[\\w\\.-]+\\.\\w+$");
    if (!email_re.match(email).hasMatch()) {
        QMessageBox::warning(this, "Error", "wrong email format !");
        reject();
        return;
    }
    QRegularExpression password_re("^^(?=.*[A-Za-z])(?=.*\\d)[A-Za-z\\d]{8,}$");
    if (!password_re.match(password).hasMatch()) {
        QMessageBox::warning(this, "Error", "password should have at least 8 characters, including at least one letter and one number.!");
        reject();
        return;
    }


    QJsonObject request;
    request["action"]="signup";
    request["username"]=username;
    request["phoneNumber"]=phoneNumber;
    request["email"]=email;
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
