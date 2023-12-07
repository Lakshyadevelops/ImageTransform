#include "ImageTransform.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    freopen("Logs.txt", "w", stdout);
    QApplication a(argc, argv);
    ImageTransform w;
    w.show();
    return a.exec();
}
