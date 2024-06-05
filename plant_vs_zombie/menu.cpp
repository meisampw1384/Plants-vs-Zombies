#include "menu.h"
#include "ui_menu.h"

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

