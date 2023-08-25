#include "loginwindow.h"

#include <QApplication>

#include "log.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginWindow w;
    logInit();
    w.show();
    return a.exec();
}
