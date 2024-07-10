#ifndef CONNECT_TO_GAME_SERVER_H
#define CONNECT_TO_GAME_SERVER_H

#include <QDialog>
#include <QTcpSocket>

namespace Ui {
class connect_to_game_server;
}

class connect_to_game_server : public QDialog
{
    Q_OBJECT

public:
    explicit connect_to_game_server(QWidget *parent = nullptr);
    ~connect_to_game_server();
    void set_userName(QString _UserName);
    QString get_userName();
public slots:
    //void onConnected();
private slots:
    void on_buttonBox_rejected();
    void on_buttonBox_accepted();
signals:
    void connectionEstablished(QString ip, int port);

private:
    Ui::connect_to_game_server *ui;
    QString user_name;
    QTcpSocket *socket;
};

#endif // CONNECT_TO_GAME_SERVER_H
