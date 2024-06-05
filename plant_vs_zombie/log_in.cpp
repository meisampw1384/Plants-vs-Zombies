#include "log_in.h"
#include "ui_log_in.h"
#include "restore_pass.h"
#include <QJsonObject>
#include <QFile>
#include <QJsonArray>
#include <QMessageBox>
#include <QJsonDocument>


log_in::log_in(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::log_in)
{
    ui->setupUi(this);
}

log_in::~log_in()
{
    delete ui;
}

void log_in::on_buttonBox_rejected()
{

}


void log_in::on_buttonBox_accepted()
{
    QString username=this->ui->line_edit_name->text();
    QString password=this->ui->line_edit_password->text();
    QFile file("information.json");

        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::warning(this, "Error", "Could not open file, if you haven't sign up, please do that!");
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
        int flag = 0;
        for (const QJsonValue &value : jsonArray) {
            QJsonObject obj = value.toObject();
            if (obj["username"].toString() == username && obj["password"].toString() == password)
            {
                QMessageBox::information(this, "Login Success", "Login successful!");
                flag = 1;
                break;
            }
        }

        if(flag)
        {
            this->accept();
        }
        else
        {
            QMessageBox::warning(this, "Login Failed", "Invalid username or password!");
            this->reject();
        }

}


void log_in::on_pushButton_clicked()
{
    restore_pass * RP = new restore_pass();
    RP->show();
}

