#include "pineapple2.h"

#include <QtGui>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PineApple2 w;
    w.show();
    return a.exec();
}
