#include "game_menu.h"
#include "ui_game_menu.h"
#include "menu.h"

game_menu::game_menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::game_menu)
{
    ui->setupUi(this);
    connect(ui->logout_button, &QPushButton::clicked, this, &game_menu::handleLogout);
}

game_menu::~game_menu()
{
    delete ui;
}

void game_menu::on_logout_button_clicked()
{
    rejected();
}

void game_menu::handleLogout()
{
    this->close();

    menu * w = new menu();
    w->show();
}

