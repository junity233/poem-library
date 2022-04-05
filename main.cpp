#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include <qtranslator.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator t;
    t.load("zh");

    a.installTranslator(&t);
    MainWindow w;
    w.show();
    return a.exec();
}
