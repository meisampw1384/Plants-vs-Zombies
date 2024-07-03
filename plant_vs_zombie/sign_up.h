#ifndef SIGN_UP_H
#define SIGN_UP_H

#include <QDialog>
#include <QTcpSocket>

namespace Ui {
class sign_up;
}

class sign_up : public QDialog
{
    Q_OBJECT

public:
    explicit sign_up(QWidget *parent = nullptr);
    ~sign_up();

private slots:
    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

    void readyResponse();



private:
    Ui::sign_up *ui;
    QTcpSocket *socket;

};

#endif // SIGN_UP_H
