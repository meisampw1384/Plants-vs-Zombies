/********************************************************************************
** Form generated from reading UI file 'restore_pass.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESTORE_PASS_H
#define UI_RESTORE_PASS_H

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

class Ui_restore_pass
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label_7;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QLabel *label_5;
    QWidget *layoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *line_edit_phone;
    QLineEdit *lineEdit_password;
    QLabel *label_8;

    void setupUi(QDialog *restore_pass)
    {
        if (restore_pass->objectName().isEmpty())
            restore_pass->setObjectName(QString::fromUtf8("restore_pass"));
        restore_pass->resize(649, 477);
        buttonBox = new QDialogButtonBox(restore_pass);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(230, 350, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label_7 = new QLabel(restore_pass);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(-120, -70, 951, 681));
        label_7->setPixmap(QPixmap(QString::fromUtf8("../images/pvz2-ea-hero-pvz2-xl.jpg.adapt.crop191x100.1200w.jpg")));
        layoutWidget = new QWidget(restore_pass);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(140, 110, 179, 121));
        QFont font;
        font.setFamilies({QString::fromUtf8("Sitka Banner")});
        font.setPointSize(15);
        layoutWidget->setFont(font);
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(29, 255, 123);"));

        verticalLayout->addWidget(label_2);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font);
        label_5->setStyleSheet(QString::fromUtf8("color: rgb(29, 255, 123);"));

        verticalLayout->addWidget(label_5);

        layoutWidget_2 = new QWidget(restore_pass);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(330, 100, 241, 151));
        verticalLayout_2 = new QVBoxLayout(layoutWidget_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        line_edit_phone = new QLineEdit(layoutWidget_2);
        line_edit_phone->setObjectName(QString::fromUtf8("line_edit_phone"));

        verticalLayout_2->addWidget(line_edit_phone);

        lineEdit_password = new QLineEdit(layoutWidget_2);
        lineEdit_password->setObjectName(QString::fromUtf8("lineEdit_password"));

        verticalLayout_2->addWidget(lineEdit_password);

        label_8 = new QLabel(restore_pass);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(180, -20, 291, 121));
        QFont font1;
        font1.setPointSize(22);
        label_8->setFont(font1);
        label_8->setStyleSheet(QString::fromUtf8("color:rgb(0, 0, 0);"));
        label_7->raise();
        buttonBox->raise();
        layoutWidget->raise();
        layoutWidget_2->raise();
        label_8->raise();

        retranslateUi(restore_pass);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, restore_pass, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, restore_pass, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(restore_pass);
    } // setupUi

    void retranslateUi(QDialog *restore_pass)
    {
        restore_pass->setWindowTitle(QCoreApplication::translate("restore_pass", "Dialog", nullptr));
        label_7->setText(QString());
        label_2->setText(QCoreApplication::translate("restore_pass", "phone number :", nullptr));
        label_5->setText(QCoreApplication::translate("restore_pass", "new password :", nullptr));
        label_8->setText(QCoreApplication::translate("restore_pass", "restore password", nullptr));
    } // retranslateUi

};

namespace Ui {
    class restore_pass: public Ui_restore_pass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESTORE_PASS_H
