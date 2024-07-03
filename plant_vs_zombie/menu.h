#ifndef MENU_H
#define MENU_H

#include <QMainWindow>
#include <QApplication>

QT_BEGIN_NAMESPACE
namespace Ui { class menu; }
QT_END_NAMESPACE

class menu : public QMainWindow
{
    Q_OBJECT

public:
    menu(QWidget *parent = nullptr);
    void showMenu();
    ~menu();

private slots:
    void on_LoginButton_clicked();
    void on_SignUp_button_clicked();

private:
    Ui::menu *ui;
};
#endif // MENU_H
