#ifndef LOG_IN_H
#define LOG_IN_H

#include <QDialog>

namespace Ui {
class log_in;
}

class log_in : public QDialog
{
    Q_OBJECT

public:
    explicit log_in(QWidget *parent = nullptr);
    ~log_in();

private slots:
    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

    void on_pushButton_clicked();

private:
    Ui::log_in *ui;
};

#endif // LOG_IN_H
