#include "connect_to_game_server.h"
#include "ui_connect_to_game_server.h"
#include <QMessageBox>
#include "game.h"

connect_to_game_server::connect_to_game_server(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::connect_to_game_server)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);
}

connect_to_game_server::~connect_to_game_server()
{
    delete ui;
}

void connect_to_game_server::on_buttonBox_rejected()
{
    reject();
}
void connect_to_game_server::set_userName(QString UserName)
{
    user_name = UserName;
}

void connect_to_game_server::on_buttonBox_accepted()
{
    QString entered_IP = ui->IP_line->text();
    QString entered_Port_str = ui->Port_line->text();
    int Port = entered_Port_str.toInt();

    //check input;

    socket->connectToHost(entered_IP, Port);
    if (socket->waitForConnected(5000))
    {
        qDebug()<<"connection established";
        socket->disconnectFromHost();
        this->close();
        game * game_windows = new game();
        game_windows->set_ip(entered_IP);
        game_windows->set_port(Port);
        game_windows->set_userName(user_name);
        game_windows->onConnected();
        game_windows->setupUI();
        game_windows->show();
    }
    else
    {
        this->close();
        QMessageBox::warning(this,"Error","connection failed !");
        reject();
    }
}
