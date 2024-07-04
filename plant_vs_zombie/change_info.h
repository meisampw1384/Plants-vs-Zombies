#ifndef CHANGE_INFO_H
#define CHANGE_INFO_H

#include <QDialog>

namespace Ui {
class change_info;
}

class change_info : public QDialog
{
    Q_OBJECT

public:
    explicit change_info(QWidget *parent = nullptr);
    ~change_info();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::change_info *ui;
};

#endif // CHANGE_INFO_H
