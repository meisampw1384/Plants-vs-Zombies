#include "menu.h"
#include "ui_menu.h"
#include "log_in.h"
#include "sign_up.h"

menu::menu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::menu)
{
    ui->setupUi(this);
    setFixedSize(1024,720);
}

menu::~menu()
{
    delete ui;
}


void menu::on_LoginButton_clicked()
{
    log_in *window_login=new log_in();
    window_login->show();
    this->hide();
    connect(window_login, &log_in::rejected, this, &menu::showMenu);
}


void menu::on_SignUp_button_clicked()
{
    sign_up *window_sign_up=new sign_up();
    window_sign_up->show();
    this->hide();
    connect(window_sign_up, &sign_up::rejected, this, &menu::showMenu);
}

void menu::showMenu(){
    this->show();
}

