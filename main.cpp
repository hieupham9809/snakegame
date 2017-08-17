#include "mainwindow.h"
#include <QApplication>
#include <snake.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    snake window;
    window.resize (300,300);
    window.show();

    return a.exec();
}
