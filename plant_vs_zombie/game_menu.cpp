#include "game_menu.h"
#include "ui_game_menu.h"

game_menu::game_menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::game_menu)
{
    ui->setupUi(this);
}

game_menu::~game_menu()
{
    delete ui;
}

void game_menu::on_logout_button_clicked()
{
    rejected();
}

