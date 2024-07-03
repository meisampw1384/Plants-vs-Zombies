#include "menu.h"
#include "server.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    menu w;
    w.show();

    return a.exec();
}
