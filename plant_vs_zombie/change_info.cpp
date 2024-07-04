#include "change_info.h"
#include "ui_change_info.h"
#include <QJsonObject>
#include <QCryptographicHash>
#include <QFile>
#include <QJsonArray>
#include <QMessageBox>
#include <QJsonDocument>

change_info::change_info(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::change_info)
{
    ui->setupUi(this);
}

change_info::~change_info()
{
    delete ui;
}

void change_info::on_buttonBox_accepted()
{
    QString new_name = this->ui->line_edit_name_2->text();
    QString new_username = this->ui->line_edit_username_2->text();
    QString new_phoneNumber = this->ui->line_edit_phonenumber_2->text();
    QString new_email = this->ui->line_edit_email_2->text();
    QString new_raw_password = this->ui->line_edit_password_2->text();

    QJsonDocument doc = readJsonFile("TMP_data.json");
    QJsonArray jsonArray = doc.array();
    bool usernameExists = false;



    if (usernameExists) {
        response["result"] = "failure";
        response["message"] = "Username already exists.";
        qDebug() << "Signup action result:" << response["result"].toString();  // Debug output
    } else {
        QJsonObject newUser;
        newUser["username"] = username;
        newUser["phoneNumber"] = phoneNumber;
        newUser["email"] = email;
        newUser["password"] = password;
        newUser["name"] = name;

        jsonArray.append(newUser);
        writeJsonFile("information.json", QJsonDocument(jsonArray));
        response["result"] = "success";
        qDebug() << "Signup action result:" << response["result"].toString();  // Debug output
    }
}

