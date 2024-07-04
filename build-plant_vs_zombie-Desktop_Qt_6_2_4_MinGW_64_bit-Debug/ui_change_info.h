/********************************************************************************
** Form generated from reading UI file 'change_info.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHANGE_INFO_H
#define UI_CHANGE_INFO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_change_info
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label_7;
    QLabel *label_8;
    QLineEdit *line_edit_phonenumber_2;
    QLineEdit *line_edit_name_2;
    QLineEdit *line_edit_password_2;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *line_edit_name;
    QLabel *line_edit_username;
    QLabel *line_edit_phonenumber;
    QLabel *line_edit_email;
    QLabel *line_edit_password;
    QLineEdit *line_edit_email_2;
    QLineEdit *line_edit_username_2;
    QLabel *label;

    void setupUi(QDialog *change_info)
    {
        if (change_info->objectName().isEmpty())
            change_info->setObjectName(QString::fromUtf8("change_info"));
        change_info->resize(761, 591);
        QFont font;
        font.setBold(false);
        change_info->setFont(font);
        buttonBox = new QDialogButtonBox(change_info);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(380, 510, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label_7 = new QLabel(change_info);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(-60, 0, 951, 681));
        label_7->setPixmap(QPixmap(QString::fromUtf8("../images/pvz2-ea-hero-pvz2-xl.jpg.adapt.crop191x100.1200w.jpg")));
        label_8 = new QLabel(change_info);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(280, -10, 331, 121));
        QFont font1;
        font1.setPointSize(22);
        label_8->setFont(font1);
        label_8->setStyleSheet(QString::fromUtf8("color:rgb(0, 0, 0);"));
        line_edit_phonenumber_2 = new QLineEdit(change_info);
        line_edit_phonenumber_2->setObjectName(QString::fromUtf8("line_edit_phonenumber_2"));
        line_edit_phonenumber_2->setGeometry(QRect(490, 251, 181, 26));
        line_edit_name_2 = new QLineEdit(change_info);
        line_edit_name_2->setObjectName(QString::fromUtf8("line_edit_name_2"));
        line_edit_name_2->setGeometry(QRect(450, 129, 221, 26));
        line_edit_password_2 = new QLineEdit(change_info);
        line_edit_password_2->setObjectName(QString::fromUtf8("line_edit_password_2"));
        line_edit_password_2->setGeometry(QRect(440, 373, 231, 26));
        line_edit_password_2->setEchoMode(QLineEdit::Password);
        layoutWidget = new QWidget(change_info);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(326, 110, 179, 301));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Sitka Banner")});
        font2.setPointSize(15);
        font2.setBold(false);
        layoutWidget->setFont(font2);
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        line_edit_name = new QLabel(layoutWidget);
        line_edit_name->setObjectName(QString::fromUtf8("line_edit_name"));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Sitka Banner")});
        font3.setPointSize(15);
        font3.setUnderline(false);
        font3.setStrikeOut(false);
        line_edit_name->setFont(font3);
        line_edit_name->setStyleSheet(QString::fromUtf8("color: rgb(29, 255, 123);"));

        verticalLayout->addWidget(line_edit_name);

        line_edit_username = new QLabel(layoutWidget);
        line_edit_username->setObjectName(QString::fromUtf8("line_edit_username"));
        QFont font4;
        font4.setFamilies({QString::fromUtf8("Sitka Banner")});
        font4.setPointSize(15);
        line_edit_username->setFont(font4);
        line_edit_username->setStyleSheet(QString::fromUtf8("\n"
"color: rgb(29, 255, 123);"));

        verticalLayout->addWidget(line_edit_username);

        line_edit_phonenumber = new QLabel(layoutWidget);
        line_edit_phonenumber->setObjectName(QString::fromUtf8("line_edit_phonenumber"));
        line_edit_phonenumber->setFont(font4);
        line_edit_phonenumber->setStyleSheet(QString::fromUtf8("color: rgb(29, 255, 123);"));

        verticalLayout->addWidget(line_edit_phonenumber);

        line_edit_email = new QLabel(layoutWidget);
        line_edit_email->setObjectName(QString::fromUtf8("line_edit_email"));
        line_edit_email->setFont(font4);
        line_edit_email->setStyleSheet(QString::fromUtf8("color: rgb(29, 255, 123);"));

        verticalLayout->addWidget(line_edit_email);

        line_edit_password = new QLabel(layoutWidget);
        line_edit_password->setObjectName(QString::fromUtf8("line_edit_password"));
        line_edit_password->setFont(font4);
        line_edit_password->setStyleSheet(QString::fromUtf8("color: rgb(29, 255, 123);"));

        verticalLayout->addWidget(line_edit_password);

        line_edit_email_2 = new QLineEdit(change_info);
        line_edit_email_2->setObjectName(QString::fromUtf8("line_edit_email_2"));
        line_edit_email_2->setGeometry(QRect(410, 312, 261, 26));
        line_edit_username_2 = new QLineEdit(change_info);
        line_edit_username_2->setObjectName(QString::fromUtf8("line_edit_username_2"));
        line_edit_username_2->setGeometry(QRect(450, 190, 221, 26));
        label = new QLabel(change_info);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(360, 430, 291, 31));
        QFont font5;
        font5.setPointSize(11);
        font5.setBold(true);
        label->setFont(font5);
        label->setStyleSheet(QString::fromUtf8("color:rgb(189, 12, 22);"));
        label_7->raise();
        buttonBox->raise();
        label_8->raise();
        line_edit_phonenumber_2->raise();
        line_edit_name_2->raise();
        line_edit_password_2->raise();
        layoutWidget->raise();
        line_edit_email_2->raise();
        line_edit_username_2->raise();
        label->raise();

        retranslateUi(change_info);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, change_info, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, change_info, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(change_info);
    } // setupUi

    void retranslateUi(QDialog *change_info)
    {
        change_info->setWindowTitle(QCoreApplication::translate("change_info", "Dialog", nullptr));
        label_7->setText(QString());
        label_8->setText(QCoreApplication::translate("change_info", "change information", nullptr));
        line_edit_name->setText(QCoreApplication::translate("change_info", "name : ", nullptr));
        line_edit_username->setText(QCoreApplication::translate("change_info", "username :", nullptr));
        line_edit_phonenumber->setText(QCoreApplication::translate("change_info", "phone number :", nullptr));
        line_edit_email->setText(QCoreApplication::translate("change_info", "email :", nullptr));
        line_edit_password->setText(QCoreApplication::translate("change_info", "password :", nullptr));
        label->setText(QCoreApplication::translate("change_info", "fill every field you wanna change", nullptr));
    } // retranslateUi

};

namespace Ui {
    class change_info: public Ui_change_info {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHANGE_INFO_H
