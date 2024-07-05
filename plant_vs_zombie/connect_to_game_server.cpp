#include "connect_to_game_server.h"
#include "ui_connect_to_game_server.h"
#include <QMessageBox>

connect_to_game_server::connect_to_game_server(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::connect_to_game_server)
{
    ui->setupUi(this);
}

connect_to_game_server::~connect_to_game_server()
{
    delete ui;
}

void connect_to_game_server::on_buttonBox_rejected()
{
    reject();
}


void connect_to_game_server::on_buttonBox_accepted()
{
    QString entered_IP = ui->lineEdit->text();


}
