/********************************************************************************
** Form generated from reading UI file 'log_in.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOG_IN_H
#define UI_LOG_IN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_log_in
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label_7;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label_3;
    QLabel *label_5;
    QWidget *layoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *line_edit_name;
    QLineEdit *line_edit_password;
    QLabel *label_8;
    QPushButton *pushButton;

    void setupUi(QDialog *log_in)
    {
        if (log_in->objectName().isEmpty())
            log_in->setObjectName(QString::fromUtf8("log_in"));
        log_in->resize(761, 591);
        buttonBox = new QDialogButtonBox(log_in);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(421, 470, 167, 29));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label_7 = new QLabel(log_in);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(-140, -1, 951, 681));
        label_7->setPixmap(QPixmap(QString::fromUtf8("../images/pvz2-ea-hero-pvz2-xl.jpg.adapt.crop191x100.1200w.jpg")));
        layoutWidget = new QWidget(log_in);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(190, 160, 121, 131));
        QFont font;
        font.setFamilies({QString::fromUtf8("Sitka Banner")});
        font.setPointSize(15);
        layoutWidget->setFont(font);
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font);
        label_3->setStyleSheet(QString::fromUtf8("\n"
"color: rgb(29, 255, 123);"));

        verticalLayout->addWidget(label_3);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font);
        label_5->setStyleSheet(QString::fromUtf8("color: rgb(29, 255, 123);"));

        verticalLayout->addWidget(label_5);

        layoutWidget_2 = new QWidget(log_in);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(330, 150, 241, 161));
        verticalLayout_2 = new QVBoxLayout(layoutWidget_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        line_edit_name = new QLineEdit(layoutWidget_2);
        line_edit_name->setObjectName(QString::fromUtf8("line_edit_name"));

        verticalLayout_2->addWidget(line_edit_name);

        line_edit_password = new QLineEdit(layoutWidget_2);
        line_edit_password->setObjectName(QString::fromUtf8("line_edit_password"));

        verticalLayout_2->addWidget(line_edit_password);

        label_8 = new QLabel(log_in);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(330, 0, 241, 121));
        QFont font1;
        font1.setPointSize(22);
        label_8->setFont(font1);
        label_8->setStyleSheet(QString::fromUtf8("color:rgb(0, 0, 0);"));
        pushButton = new QPushButton(log_in);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(290, 470, 122, 29));
        label_7->raise();
        buttonBox->raise();
        layoutWidget->raise();
        layoutWidget_2->raise();
        label_8->raise();
        pushButton->raise();

        retranslateUi(log_in);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, log_in, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, log_in, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(log_in);
    } // setupUi

    void retranslateUi(QDialog *log_in)
    {
        log_in->setWindowTitle(QCoreApplication::translate("log_in", "Dialog", nullptr));
        label_7->setText(QString());
        label_3->setText(QCoreApplication::translate("log_in", "username :", nullptr));
        label_5->setText(QCoreApplication::translate("log_in", "password :", nullptr));
        label_8->setText(QCoreApplication::translate("log_in", "log in", nullptr));
        pushButton->setText(QCoreApplication::translate("log_in", "restore password", nullptr));
    } // retranslateUi

};

namespace Ui {
    class log_in: public Ui_log_in {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOG_IN_H
