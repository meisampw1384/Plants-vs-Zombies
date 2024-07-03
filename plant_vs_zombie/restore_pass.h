#ifndef RESTORE_PASS_H
#define RESTORE_PASS_H

#include <QDialog>
#include <QTcpSocket>

namespace Ui {
class restore_pass;
}

class restore_pass : public QDialog
{
    Q_OBJECT

public:
    explicit restore_pass(QWidget *parent = nullptr);
    ~restore_pass();

private slots:
    void on_buttonBox_accepted();
    void readyResponse();

private:
    Ui::restore_pass *ui;
    QTcpSocket *socket;

};

#endif // RESTORE_PASS_H
