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
}

restore_pass::~restore_pass()
{
    delete ui;
}

void restore_pass::on_buttonBox_accepted()
{
    QString phone_number=this->ui->line_edit_phone->text();
    QString new_password=this->ui->lineEdit_password->text();

        QFile file("information.json");

        if (!file.open(QIODevice::ReadWrite)) {
            QMessageBox::warning(this, "Error", "Could not open file. If you haven't signed up, please do so.");
            return;
        }

        QByteArray data = file.readAll();
        file.close();

        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
        if (jsonDoc.isNull() || !jsonDoc.isArray()) {
            QMessageBox::warning(this, "Error", "Invalid JSON format");
            return;
        }

        QJsonArray jsonArray = jsonDoc.array();
        bool userFound = false;

        for (int i=0;i<jsonArray.size();i++)
        {

            QJsonObject obj = jsonArray[i].toObject();
            if (obj["phoneNumber"].toString() == phone_number) {
                obj["password"] = new_password;
                jsonArray[i]=obj;
                userFound = true;
                break;
            }
        }

        if (userFound) {
            QJsonDocument updatedJsonDoc(jsonArray);

            if (!file.open(QIODevice::WriteOnly)) {
                QMessageBox::warning(this, "Error", "Could not open file for writing");
                return;
            }

            file.write(updatedJsonDoc.toJson());
            file.close();

            QMessageBox::information(this, "Password Changed", "Password changed successfully!");
            this->accept();
        } else {
            QMessageBox::warning(this, "Error", "Phone number not found. Please check and try again.");
        }

}

