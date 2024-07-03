#ifndef GAME_MENU_H
#define GAME_MENU_H

#include <QDialog>

namespace Ui {
class game_menu;
}

class game_menu : public QDialog
{
    Q_OBJECT

public:
    explicit game_menu(QWidget *parent = nullptr);
    ~game_menu();

private slots:
    void on_logout_button_clicked();
    void handleLogout();

private:
    Ui::game_menu *ui;
};

#endif // GAME_MENU_H
