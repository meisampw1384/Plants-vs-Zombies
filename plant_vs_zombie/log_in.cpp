#include "log_in.h"
#include "ui_log_in.h"
#include "restore_pass.h"
#include <QJsonObject>
#include <QFile>
#include <QTcpSocket>
#include <QJsonArray>
#include <QMessageBox>
#include <QJsonDocument>


log_in::log_in(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::log_in)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead,this,&log_in::readResponse);

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
    QString username = ui->line_edit_name->text();
     QString password = ui->line_edit_password->text();

     QJsonObject request;
     request["action"] = "login";
     request["username"] = username;
     request["password"] = password;

     QJsonDocument doc(request);
     socket->connectToHost("127.0.0.1", 1234);
     if (socket->waitForConnected()) {
         socket->write(doc.toJson());
     }

}


void log_in::on_pushButton_clicked()
{
    restore_pass * RP = new restore_pass();
    RP->show();
}

void log_in::readResponse()
{
   QByteArray response = socket->readAll();
   QJsonDocument doc = QJsonDocument::fromJson(response);
   QJsonObject obj=doc.object();

   if (obj["result"].toString() == "success"){
       QMessageBox::information(this,"Login Success","Login successful!");
       accept();
   }
   else {
       QMessageBox::warning(this,"Login Failed","Invalid username or password!");
       reject();
   }
}

