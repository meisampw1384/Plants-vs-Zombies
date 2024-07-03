/********************************************************************************
** Form generated from reading UI file 'game_menu.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAME_MENU_H
#define UI_GAME_MENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_game_menu
{
public:
    QLabel *label;
    QPushButton *LoginButton;
    QPushButton *LoginButton_2;
    QPushButton *LoginButton_3;
    QPushButton *logout_button;

    void setupUi(QDialog *game_menu)
    {
        if (game_menu->objectName().isEmpty())
            game_menu->setObjectName(QString::fromUtf8("game_menu"));
        game_menu->resize(1024, 720);
        label = new QLabel(game_menu);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, -10, 1141, 731));
        label->setPixmap(QPixmap(QString::fromUtf8("../images/game_menu.jpg")));
        LoginButton = new QPushButton(game_menu);
        LoginButton->setObjectName(QString::fromUtf8("LoginButton"));
        LoginButton->setGeometry(QRect(340, 440, 351, 61));
        QFont font;
        font.setFamilies({QString::fromUtf8("Snap ITC")});
        font.setPointSize(16);
        LoginButton->setFont(font);
        LoginButton->setCursor(QCursor(Qt::PointingHandCursor));
        LoginButton->setMouseTracking(true);
        LoginButton->setTabletTracking(false);
        LoginButton->setStyleSheet(QString::fromUtf8("background-color: #644370; /* Green */\n"
"border-color: #2196F3;\n"
"  border: none;\n"
"  color: white;\n"
"  text-align: center;\n"
"  display: inline-block;\n"
"  font-size:25;\n"
"  cursor: pointer;\n"
"border-radius: 10px;"));
        LoginButton_2 = new QPushButton(game_menu);
        LoginButton_2->setObjectName(QString::fromUtf8("LoginButton_2"));
        LoginButton_2->setGeometry(QRect(340, 360, 351, 61));
        LoginButton_2->setFont(font);
        LoginButton_2->setCursor(QCursor(Qt::PointingHandCursor));
        LoginButton_2->setMouseTracking(true);
        LoginButton_2->setTabletTracking(false);
        LoginButton_2->setStyleSheet(QString::fromUtf8("background-color: #644370; /* Green */\n"
"border-color: #2196F3;\n"
"  border: none;\n"
"  color: white;\n"
"  text-align: center;\n"
"  display: inline-block;\n"
"  font-size:25;\n"
"  cursor: pointer;\n"
"border-radius: 10px;"));
        LoginButton_3 = new QPushButton(game_menu);
        LoginButton_3->setObjectName(QString::fromUtf8("LoginButton_3"));
        LoginButton_3->setGeometry(QRect(310, 260, 411, 81));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Snap ITC")});
        font1.setPointSize(24);
        LoginButton_3->setFont(font1);
        LoginButton_3->setCursor(QCursor(Qt::PointingHandCursor));
        LoginButton_3->setMouseTracking(true);
        LoginButton_3->setTabletTracking(false);
        LoginButton_3->setStyleSheet(QString::fromUtf8("background-color: #644370; /* Green */\n"
"border-color: #2196F3;\n"
"  border: none;\n"
"  color: white;\n"
"  text-align: center;\n"
"  display: inline-block;\n"
"  font-size:25;\n"
"  cursor: pointer;\n"
"border-radius: 10px;"));
        logout_button = new QPushButton(game_menu);
        logout_button->setObjectName(QString::fromUtf8("logout_button"));
        logout_button->setGeometry(QRect(420, 520, 191, 61));
        logout_button->setFont(font);
        logout_button->setCursor(QCursor(Qt::PointingHandCursor));
        logout_button->setMouseTracking(true);
        logout_button->setTabletTracking(false);
        logout_button->setStyleSheet(QString::fromUtf8("background-color: #7b3432; /* Green */\n"
"border-color: #2196F3;\n"
"  border: none;\n"
"  color: white;\n"
"  text-align: center;\n"
"  display: inline-block;\n"
"  font-size:25;\n"
"  cursor: pointer;\n"
"border-radius: 10px;"));

        retranslateUi(game_menu);

        QMetaObject::connectSlotsByName(game_menu);
    } // setupUi

    void retranslateUi(QDialog *game_menu)
    {
        game_menu->setWindowTitle(QCoreApplication::translate("game_menu", "Dialog", nullptr));
        label->setText(QString());
        LoginButton->setText(QCoreApplication::translate("game_menu", "games history", nullptr));
        LoginButton_2->setText(QCoreApplication::translate("game_menu", "change information", nullptr));
        LoginButton_3->setText(QCoreApplication::translate("game_menu", "START", nullptr));
        logout_button->setText(QCoreApplication::translate("game_menu", "logout", nullptr));
    } // retranslateUi

};

namespace Ui {
    class game_menu: public Ui_game_menu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAME_MENU_H
