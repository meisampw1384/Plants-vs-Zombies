#include "restore_pass.h"
#include "ui_restore_pass.h"

restore_pass::restore_pass(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::restore_pass)
{
    ui->setupUi(this);
}

restore_pass::~restore_pass()
{
    delete ui;
}
