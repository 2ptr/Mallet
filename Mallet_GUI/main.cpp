#include "Mallet_GUI.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Mallet_GUI w;
    w.show();
    return a.exec();
}
