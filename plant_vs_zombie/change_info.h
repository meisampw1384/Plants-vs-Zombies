#ifndef CHANGE_INFO_H
#define CHANGE_INFO_H

#include <QDialog>
#include <QObject>
#include <QJsonObject>
#include <QTcpSocket>

namespace Ui {
class change_info;
}

class change_info : public QDialog
{
    Q_OBJECT

public:
    explicit change_info(QWidget *parent = nullptr);
    void set_user_name(QString _userName);
    QString get_user_name();
    void readyRespond();
    ~change_info();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::change_info *ui;
    QString user_name;
    QTcpSocket *socket;
};

#endif // CHANGE_INFO_H
