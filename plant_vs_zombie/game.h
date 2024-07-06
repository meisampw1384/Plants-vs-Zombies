#ifndef GAME_H
#define GAME_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTimer>

namespace Ui {
class game;
}

class game : public QMainWindow
{
    Q_OBJECT

public:
    explicit game(QWidget *parent = nullptr);
    ~game();
private slots:
    void updateCountdown();
private:
    Ui::game *ui;
    QTcpSocket *socket;
    QTimer *timer;
    int remainingTime;

    void connect_to_server(const QString& ip, int port);
    void setupUI();

};

#endif // GAME_H
