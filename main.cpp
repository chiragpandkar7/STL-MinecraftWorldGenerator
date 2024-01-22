#include "stdafx.h"
#include "Visualizer.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Visualizer w;
    w.show();
    return a.exec();
}
