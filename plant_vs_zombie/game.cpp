#include "game.h"
#include "ui_game.h"
#include <QMessageBox>
#include <QDebug>
#include <QJsonDocument>

game::game(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::game)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);
    timer = new QTimer(this);
    remainingTime = 210;

    connect(timer, &QTimer::timeout, this, &game::updateCountdown);
    connect(socket, &QTcpSocket::readyRead, this, &game::onReadyRead);
    connect(socket, &QTcpSocket::connected, this, &game::onConnected);
    connect(socket, &QTcpSocket::disconnected, this, &game::onDisconnected);

    setupUI();

    timer->start(1000);

    // Connect to the server
    connect_to_server(ip, port); // Replace with your server IP and port
}

game::~game()
{
    delete ui;
}

void game::onConnected()
{
    qDebug() << "Connected to server";
    qDebug() << "Connected to server";
    QJsonObject request;
    request["action"] = "set_role";
    request["role"] = role;

    QJsonDocument doc(request);
    QByteArray data = doc.toJson();
    socket->write(data);
    socket->flush();
}

void game::onDisconnected()
{
    qDebug() << "Disconnected from server";
    QMessageBox::warning(this, "Disconnected", "Disconnected from server.");
}

void game::updateCountdown()
{
    if (remainingTime > 0) {
        remainingTime--;
        int minutes = remainingTime / 60;
        int seconds = remainingTime % 60;
        ui->remaining_time_label->setText(QString("%1:%2").arg(minutes, 2, 10, QChar('0')).arg(seconds, 2, 10, QChar('0')));
    } else
    {
        timer->stop();
        QMessageBox::information(this, "Game Over", "The game has ended!");
    }
}

void game::connect_to_server(const QString &ip, int port)
{
    socket->connectToHost(ip, port);
}

void game::onReadyRead()
{
    QByteArray data = socket->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject response = doc.object();

    processResponse(response);
}

void game::processResponse(const QJsonObject &response)
{
    QString action = response["action"].toString();
    if (action == "update") {
        QJsonArray gameState = response["game_state"].toArray();
        updateGameState(gameState);
    } else {
        // Handle other responses as needed
    }
}

void game::set_ip(QString _ip)
{
    ip=_ip;
}
void game::set_port(int _port){
    port=_port;
}
void game::set_role(QString _role)
{
    role = _role;
}
void game::sendMoveRequest(const QString &entityType, int entityId, const QString &direction)
{
    QJsonObject request;
    request["action"] = "move";
    request["entity_type"] = entityType;
    request["entity_id"] = entityId;
    request["direction"] = direction;

    QJsonDocument doc(request);
    QByteArray data = doc.toJson();
    socket->write(data);
    socket->flush();
}

void game::updateGameState(const QJsonArray &gameState)
{
    // Update the game state in the UI based on the received gameState
    // Example: Update positions of entities on the game field
}

void game::setupUI()
{
    ui->remaining_time_label->setText("3:30");
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
}

void game::on_pushButton_clicked()
{
    socket->disconnect();
    qDebug() << "quit game";
}





void game::on_tall_Z_Pushbutton_clicked()
{

}


void game::on_Reg_zombie_pushbutton_clicked()
{

}


void game::on_purple_pushbutton_clicked()
{

}


void game::on_leaf_Z_pushbutton_clicked()
{

}


void game::on_bucket_Z_pushbutton_clicked()
{

}


void game::on_astro_Z_pushbutton_clicked()
{

}


void game::on_boom_Pushbutton_clicked()
{

}


void game::on_Jalo_P_button_clicked()
{

}


void game::on_peashoot_Pushbutton_clicked()
{

}


void game::on_twopeashoot_Pushbutton_clicked()
{

}


void game::on_wallnut_Pushbutton_clicked()
{

}


void game::on_Plum_mine_pushbutton_clicked()
{

}

