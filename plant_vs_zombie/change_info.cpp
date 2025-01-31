#include "change_info.h"
#include "ui_change_info.h"
#include <QJsonObject>
#include <QCryptographicHash>
#include <QFile>
#include <QJsonArray>
#include <QMessageBox>
#include "game_menu.h"
#include <QJsonDocument>

change_info::change_info(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::change_info)
{
    ui->setupUi(this);
    socket=new QTcpSocket(this);
    connect(socket,&QTcpSocket::readyRead,this,&change_info::readyRespond);
}

void change_info::set_user_name(QString _userName)
{
    user_name=_userName;
}

QString change_info::get_user_name()
{
    return user_name;
}

void change_info::readyRespond()
{
    QByteArray response = socket->readAll();
    qDebug() << "Received response:" << response;
    QJsonDocument doc = QJsonDocument::fromJson(response);
    QJsonObject obj = doc.object();

    if (obj["result"].toString() == "success") {
        QMessageBox::information(this, "Change Info", "Information updated successfully!");
        accept();
        this->close();
        game_menu *gm=new game_menu();
        gm->set_user_name(obj["user_name"].toString());
        gm->show();

    } else {
        QMessageBox::warning(this, "Change Info Failed", "Failed to update information.");
        this->close();
        game_menu *gm=new game_menu();
        gm->show();
        reject();
    }

    // Disconnect the socket after handling the response
    socket->disconnectFromHost();
}


change_info::~change_info()
{
    delete ui;
}

void change_info::on_buttonBox_accepted()
{
    QString prev_user_name=this->get_user_name();
    QString new_name = this->ui->line_edit_name_2->text();
    QString new_username = this->ui->line_edit_username_2->text();
    QString new_phoneNumber = this->ui->line_edit_phonenumber_2->text();
    QString new_email = this->ui->line_edit_email_2->text();
    QString new_raw_password = this->ui->line_edit_password_2->text();

    if(new_name.size() < 3 and new_name.size() != 0)
    {
        QMessageBox::warning(this, "Error", "name should have at least 3 characters");
        reject();
        return;
    }

    QRegularExpression phoneNumber_re("^0\\d{10}$");
    if (!phoneNumber_re.match(new_phoneNumber).hasMatch() and new_phoneNumber.size() != 0 ) {
        QMessageBox::warning(this, "Error", "phone number should have 11 digits and starts with 0 !");
        reject();
        return;
    }

    QRegularExpression username_re("^[a-zA-Z0-9_]{8,}$");
    if (!username_re.match(new_username).hasMatch() and new_username.size() != 0) {
        QMessageBox::warning(this, "Error", "username must have at least 8 characters");
        reject();
        return;
    }

    QRegularExpression email_re("^[\\w\\.]+@[\\w\\.-]+\\.\\w+$");
    if (!email_re.match(new_email).hasMatch() and new_email.size() != 0) {
        QMessageBox::warning(this, "Error", "wrong email format !");
        reject();
        return;
    }
    QRegularExpression password_re("^^(?=.*[A-Za-z])(?=.*\\d)[A-Za-z\\d]{8,}$");
    if (!password_re.match(new_raw_password).hasMatch() and new_raw_password.size() != 0) {
        QMessageBox::warning(this, "Error", "password should have at least 8 characters, including at least one letter and one number.!");
        reject();
        return;
    }


    QByteArray hash = QCryptographicHash::hash(new_raw_password.toUtf8(), QCryptographicHash::Sha256);
    QString password = QString(hash.toHex());

    QJsonObject request;
    request["action"]="change_inf";
    request["prev_username"]=prev_user_name;
    request["new_name"]=new_name;
    request["new_username"]=new_username;
    request["new_phoneNumber"]=new_phoneNumber;
    request["new_email"]=new_email;
    request["new_password"]=password;

    QJsonDocument doc(request);
    QByteArray data=doc.toJson();

    socket->connectToHost("127.0.0.1",1234);

    if (socket->waitForConnected(5000)){
        qDebug()<<"connection established";

        socket->write(data);
        socket->flush();

        if (!socket->waitForReadyRead(5000)){
            qDebug() << "No response from server";
            QMessageBox::warning(this, "Error", "No response from the server.");
            reject();
        }
    }
}


void change_info::on_buttonBox_rejected()
{

}

