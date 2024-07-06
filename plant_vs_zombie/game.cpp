#include "game.h"
#include "ui_game.h"

game::game(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::game)
{
    ui->setupUi(this);
//    QPixmap image("path_to_your_image.png");
//        ImageCellWidget *imageWidget = new ImageCellWidget();
//        imageWidget->setImage(image);

//        QTableWidgetItem *item = new QTableWidgetItem();
//        ui->tableWidget->setCellWidget(0, 0, imageWidget);
}

game::~game()
{
    delete ui;
}

