#include "game_menu.h"
#include "ui_game_menu.h"
#include "change_info.h"
#include "menu.h"
#include "connect_to_game_server.h"

game_menu::game_menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::game_menu)
{
    ui->setupUi(this);
    connect(ui->logout_button, &QPushButton::clicked, this, &game_menu::handleLogout);
}

void game_menu::set_user_name(QString user_name)
{
    userName=user_name;
}
QString game_menu::get_user_name(){
    return userName;
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

void game_menu::on_change_information_button_clicked()
{
    this->close();

    change_info * ch= new change_info();
    ch->set_user_name(this->get_user_name());//send information to the change_info
    ch->show();
    connect(ch, &game_menu::rejected, this, &game_menu::show_menu);
}

void game_menu::show_menu(){
    this->show();
}


void game_menu::on_Start_button_clicked()
{
    this->close();

    connect_to_game_server * ctgs = new connect_to_game_server();
    ctgs->show();
    connect(ctgs, &game_menu::rejected, this, &game_menu::show_menu);
}

