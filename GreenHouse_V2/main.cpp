#include <QApplication>

#include "mainwindow.h"
#include "welcomewindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    welcomewindow welcome;
    welcome.showFullScreen();

    return app.exec();
}
