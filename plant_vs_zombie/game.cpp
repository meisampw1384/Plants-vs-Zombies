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
    // Optionally, send initial requests or data to the server
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
        if(ui->progressBar_Sun->value() < 100)
        {
            int current = ui->progressBar_Sun->value();
            ui->progressBar_Sun->setValue(current + 20);
        }
        if(ui->progressBar_brain->value() < 100)
        {
            int current = ui->progressBar_brain->value();
            ui->progressBar_brain->setValue(current + 20);
        }
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

    // Setup the progress bars
    ui->progressBar_Sun->setRange(0, 100);
    ui->progressBar_Sun->setValue(0);
    ui->progressBar_brain->setRange(0, 100);
    ui->progressBar_brain->setValue(0);

    // Setup the table widget with some rows and columns
    ui->field_table->setRowCount(6);
    ui->field_table->setColumnCount(22);

    // Sample images (ensure the paths or resources are correct)
}

void game::on_pushButton_clicked()
{
    socket->disconnect();
    qDebug() << "quit game";
}

void game::on_astro_Z_2_clicked()
{

}


void game::on_wallnut_P_clicked()
{

}


void game::on_twopeashoot_P_2_clicked()
{

}


void game::on_peashoot_P_clicked()
{

}


void game::on_Jalo_P_clicked()
{

}


void game::on_boom_P_clicked()
{

}


void game::on_astro_Z_clicked()
{

}


void game::on_bucket_Z_clicked()
{

}


void game::on_leaf_Z_clicked()
{

}


void game::on_pushButton_4_clicked()
{

}


void game::on_pushButton_5_clicked()
{

}


void game::on_twopeashoot_P_clicked()
{

}

