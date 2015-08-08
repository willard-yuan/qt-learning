#include "imageapp.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ImageApp w;
    w.show();

    return a.exec();
}
