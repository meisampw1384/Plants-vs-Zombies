/********************************************************************************
** Form generated from reading UI file 'menu.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MENU_H
#define UI_MENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_menu
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QPushButton *LoginButton;
    QPushButton *SignUp_button;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *menu)
    {
        if (menu->objectName().isEmpty())
            menu->setObjectName(QString::fromUtf8("menu"));
        menu->resize(1024, 720);
        centralwidget = new QWidget(menu);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 0, 1021, 671));
        label->setPixmap(QPixmap(QString::fromUtf8("../images/background_menu.png")));
        LoginButton = new QPushButton(centralwidget);
        LoginButton->setObjectName(QString::fromUtf8("LoginButton"));
        LoginButton->setGeometry(QRect(360, 440, 281, 61));
        QFont font;
        font.setFamilies({QString::fromUtf8("Snap ITC")});
        font.setPointSize(16);
        LoginButton->setFont(font);
        LoginButton->setCursor(QCursor(Qt::PointingHandCursor));
        LoginButton->setMouseTracking(true);
        LoginButton->setTabletTracking(false);
        LoginButton->setStyleSheet(QString::fromUtf8("background-color: #04AA6D; /* Green */\n"
"border-color: #2196F3;\n"
"  border: none;\n"
"  color: white;\n"
"  text-align: center;\n"
"  display: inline-block;\n"
"  font-size:25;\n"
"  cursor: pointer;\n"
"border-radius: 10px;"));
        SignUp_button = new QPushButton(centralwidget);
        SignUp_button->setObjectName(QString::fromUtf8("SignUp_button"));
        SignUp_button->setGeometry(QRect(360, 500, 281, 61));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Snap ITC")});
        SignUp_button->setFont(font1);
        SignUp_button->setCursor(QCursor(Qt::PointingHandCursor));
        SignUp_button->setMouseTracking(true);
        SignUp_button->setStyleSheet(QString::fromUtf8("background-color:#f3d027; /* Green */\n"
"border-color: #2196F3;\n"
"  border: none;\n"
"  color: white;\n"
"  text-align: center;\n"
"  display: inline-block;\n"
"  font-size: 25px;\n"
"  cursor: pointer;\n"
"border-radius: 10px;"));
        menu->setCentralWidget(centralwidget);
        menubar = new QMenuBar(menu);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1024, 25));
        menu->setMenuBar(menubar);
        statusbar = new QStatusBar(menu);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        menu->setStatusBar(statusbar);

        retranslateUi(menu);

        QMetaObject::connectSlotsByName(menu);
    } // setupUi

    void retranslateUi(QMainWindow *menu)
    {
        menu->setWindowTitle(QCoreApplication::translate("menu", "menu", nullptr));
        label->setText(QString());
        LoginButton->setText(QCoreApplication::translate("menu", "Log in", nullptr));
        SignUp_button->setText(QCoreApplication::translate("menu", "Sign up", nullptr));
    } // retranslateUi

};

namespace Ui {
    class menu: public Ui_menu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENU_H
