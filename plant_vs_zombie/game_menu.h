#ifndef GAME_MENU_H
#define GAME_MENU_H

#include <QDialog>
#include <QJsonObject>

namespace Ui {
class game_menu;
}

class game_menu : public QDialog
{
    Q_OBJECT

public:
    explicit game_menu(QWidget *parent = nullptr);
    void set_user_name(QString user_name);
    QString get_user_name();
    void show_menu();
    ~game_menu();

private slots:
    void on_logout_button_clicked();
    void handleLogout();
    void on_change_information_button_clicked();

    void on_Start_button_clicked();

private:
    Ui::game_menu *ui;
    QString userName;
};

#endif // GAME_MENU_H
