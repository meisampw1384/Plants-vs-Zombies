/********************************************************************************
** Form generated from reading UI file 'sign_up.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGN_UP_H
#define UI_SIGN_UP_H

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

class Ui_sign_up
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label_4;
    QLabel *label_7;
    QLabel *label_8;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *line_edit_name;
    QLabel *line_edit_username;
    QLabel *line_edit_phonenumber;
    QLabel *line_edit_email;
    QLabel *line_edit_password;
    QLineEdit *line_edit_name_2;
    QLineEdit *line_edit_username_2;
    QLineEdit *line_edit_phonenumber_2;
    QLineEdit *line_edit_email_2;
    QLineEdit *line_edit_password_2;

    void setupUi(QDialog *sign_up)
    {
        if (sign_up->objectName().isEmpty())
            sign_up->setObjectName(QString::fromUtf8("sign_up"));
        sign_up->resize(761, 591);
        buttonBox = new QDialogButtonBox(sign_up);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(210, 460, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Save);
        label_4 = new QLabel(sign_up);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(680, 230, 63, 20));
        label_7 = new QLabel(sign_up);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(-140, -10, 951, 681));
        label_7->setPixmap(QPixmap(QString::fromUtf8("../images/pvz2-ea-hero-pvz2-xl.jpg.adapt.crop191x100.1200w.jpg")));
        label_8 = new QLabel(sign_up);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(320, -30, 241, 121));
        QFont font;
        font.setPointSize(22);
        label_8->setFont(font);
        label_8->setStyleSheet(QString::fromUtf8("color:rgb(0, 0, 0);"));
        layoutWidget = new QWidget(sign_up);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(210, 80, 179, 301));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Sitka Banner")});
        font1.setPointSize(15);
        layoutWidget->setFont(font1);
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        line_edit_name = new QLabel(layoutWidget);
        line_edit_name->setObjectName(QString::fromUtf8("line_edit_name"));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Sitka Banner")});
        font2.setPointSize(15);
        font2.setUnderline(false);
        font2.setStrikeOut(false);
        line_edit_name->setFont(font2);
        line_edit_name->setStyleSheet(QString::fromUtf8("color: rgb(29, 255, 123);"));

        verticalLayout->addWidget(line_edit_name);

        line_edit_username = new QLabel(layoutWidget);
        line_edit_username->setObjectName(QString::fromUtf8("line_edit_username"));
        line_edit_username->setFont(font1);
        line_edit_username->setStyleSheet(QString::fromUtf8("\n"
"color: rgb(29, 255, 123);"));

        verticalLayout->addWidget(line_edit_username);

        line_edit_phonenumber = new QLabel(layoutWidget);
        line_edit_phonenumber->setObjectName(QString::fromUtf8("line_edit_phonenumber"));
        line_edit_phonenumber->setFont(font1);
        line_edit_phonenumber->setStyleSheet(QString::fromUtf8("color: rgb(29, 255, 123);"));

        verticalLayout->addWidget(line_edit_phonenumber);

        line_edit_email = new QLabel(layoutWidget);
        line_edit_email->setObjectName(QString::fromUtf8("line_edit_email"));
        line_edit_email->setFont(font1);
        line_edit_email->setStyleSheet(QString::fromUtf8("color: rgb(29, 255, 123);"));

        verticalLayout->addWidget(line_edit_email);

        line_edit_password = new QLabel(layoutWidget);
        line_edit_password->setObjectName(QString::fromUtf8("line_edit_password"));
        line_edit_password->setFont(font1);
        line_edit_password->setStyleSheet(QString::fromUtf8("color: rgb(29, 255, 123);"));

        verticalLayout->addWidget(line_edit_password);

        line_edit_name_2 = new QLineEdit(sign_up);
        line_edit_name_2->setObjectName(QString::fromUtf8("line_edit_name_2"));
        line_edit_name_2->setGeometry(QRect(334, 99, 221, 26));
        line_edit_username_2 = new QLineEdit(sign_up);
        line_edit_username_2->setObjectName(QString::fromUtf8("line_edit_username_2"));
        line_edit_username_2->setGeometry(QRect(334, 160, 221, 26));
        line_edit_phonenumber_2 = new QLineEdit(sign_up);
        line_edit_phonenumber_2->setObjectName(QString::fromUtf8("line_edit_phonenumber_2"));
        line_edit_phonenumber_2->setGeometry(QRect(374, 221, 181, 26));
        line_edit_email_2 = new QLineEdit(sign_up);
        line_edit_email_2->setObjectName(QString::fromUtf8("line_edit_email_2"));
        line_edit_email_2->setGeometry(QRect(294, 282, 261, 26));
        line_edit_password_2 = new QLineEdit(sign_up);
        line_edit_password_2->setObjectName(QString::fromUtf8("line_edit_password_2"));
        line_edit_password_2->setGeometry(QRect(324, 343, 231, 26));
        label_7->raise();
        layoutWidget->raise();
        buttonBox->raise();
        label_4->raise();
        label_8->raise();
        line_edit_name_2->raise();
        line_edit_username_2->raise();
        line_edit_phonenumber_2->raise();
        line_edit_email_2->raise();
        line_edit_password_2->raise();

        retranslateUi(sign_up);
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, sign_up, qOverload<>(&QDialog::reject));
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, sign_up, qOverload<>(&QDialog::accept));

        QMetaObject::connectSlotsByName(sign_up);
    } // setupUi

    void retranslateUi(QDialog *sign_up)
    {
        sign_up->setWindowTitle(QCoreApplication::translate("sign_up", "Dialog", nullptr));
        label_4->setText(QString());
        label_7->setText(QString());
        label_8->setText(QCoreApplication::translate("sign_up", "Sign up", nullptr));
        line_edit_name->setText(QCoreApplication::translate("sign_up", "name : ", nullptr));
        line_edit_username->setText(QCoreApplication::translate("sign_up", "username :", nullptr));
        line_edit_phonenumber->setText(QCoreApplication::translate("sign_up", "phone number :", nullptr));
        line_edit_email->setText(QCoreApplication::translate("sign_up", "email :", nullptr));
        line_edit_password->setText(QCoreApplication::translate("sign_up", "password :", nullptr));
    } // retranslateUi

};

namespace Ui {
    class sign_up: public Ui_sign_up {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGN_UP_H
