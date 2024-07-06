#include "game.h"
#include "ui_game.h"
#include <QMessageBox>

game::game(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::game)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);
    timer = new QTimer(this);
    remainingTime=210;


    connect(timer,&QTimer::timeout,this, &game::updateCountdown);


    setupUI();

    timer->start(1000);

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

void game::updateCountdown()
{
    if (remainingTime > 0) {
        remainingTime--;
        int minutes = remainingTime / 60;
        int seconds = remainingTime % 60;
        ui->remaining_time_label->setText(QString("%1:%2").arg(minutes, 2, 10, QChar('0')).arg(seconds, 2, 10, QChar('0')));
    } else {
        timer->stop();
        QMessageBox::information(this, "Game Over", "The game has ended!");
    }
}


void game::connect_to_server(const QString &ip, int port)
{
    socket->connectToHost(ip,port);
}

void game::setupUI(){
    ui->remaining_time_label->setText("3:30");

        // Setup the progress bars
    ui->progressBar_Sun->setRange(0, 100);
    ui->progressBar_Sun->setValue(0);
    ui->progressBar_brain->setRange(0, 100);
    ui->progressBar_brain->setValue(0);

    // Setup the table widget with some rows and columns
    ui->field_table->setRowCount(6);
    ui->field_table->setColumnCount(22);

    // Sample images (ensure the paths or resources are correct
}
