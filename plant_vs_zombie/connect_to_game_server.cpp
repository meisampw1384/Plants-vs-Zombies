#include "connect_to_game_server.h"
#include "ui_connect_to_game_server.h"
#include <QMessageBox>
#include "game.h"

connect_to_game_server::connect_to_game_server(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::connect_to_game_server),
    socket(new QTcpSocket(this))
{
    ui->setupUi(this);
    connect(socket, &QTcpSocket::connected, this, &connect_to_game_server::onConnected);
}

connect_to_game_server::~connect_to_game_server()
{
    delete ui;
}

void connect_to_game_server::set_userName(QString _UserName)
{
    user_name = _UserName;
}

QString connect_to_game_server::get_userName()
{
    return user_name;
}

void connect_to_game_server::on_buttonBox_rejected()
{
    reject();
}

void connect_to_game_server::on_buttonBox_accepted()
{
    QString entered_IP = ui->IP_line->text();
    QString entered_Port_str = ui->Port_line->text();
    int Port = entered_Port_str.toInt();

    // Check input validity
    if (entered_IP.isEmpty() || entered_Port_str.isEmpty() || Port <= 0) {
        QMessageBox::warning(this, "Input Error", "Please enter a valid IP address and port number.");
        return;
    }

    socket->connectToHost(entered_IP, Port);
    if (!socket->waitForConnected(5000)) {
        QMessageBox::warning(this, "Error", "Connection failed!");
        reject();
    }
}

void connect_to_game_server::onConnected()
{
    qDebug() << "Connection established";
    game *game_window = new game();
    game_window->set_userName(user_name);
    game_window->set_ip(socket->peerAddress().toString());
    game_window->set_port(socket->peerPort());
    game_window->setSocket(socket);
    game_window->onConnected();


    game_window->show();
    this->close();
}




