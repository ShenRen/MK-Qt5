#include "qtshowerror.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtShowError w(argc, argv, NULL);
    w.show();

    return a.exec();
}
