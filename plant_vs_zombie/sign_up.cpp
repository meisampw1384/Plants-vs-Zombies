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

    QJsonObject jsonObject;
    jsonObject["name"] = name;
    jsonObject["username"] = username;
    jsonObject["phoneNumber"] = phoneNumber;
    jsonObject["email"] = email;
    jsonObject["password"] = password;

    QFile file("information.json");
    QJsonArray jsonArray;

    if (file.exists()) {
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::warning(this, "Error", "Could not open file for reading");
            return;
        }

        QByteArray data = file.readAll();
        file.close();

        QJsonDocument existingDoc = QJsonDocument::fromJson(data);
        if (!existingDoc.isArray()) {
            QMessageBox::warning(this, "Error", "Invalid JSON format");
            return;
        }

        jsonArray = existingDoc.array();
    }

    jsonArray.append(jsonObject);

    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(this, "Error", "Could not open file for writing");
        return;
    }

    QJsonDocument jsonDoc(jsonArray);
    file.write(jsonDoc.toJson());
    file.close();

    QMessageBox::information(this, "Success", "Sign up successful");
    this->accept();
}
