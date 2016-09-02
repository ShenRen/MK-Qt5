#include "QtAxis.h"

int main( int argc, char ** argv )
{
    QApplication a( argc, argv );
    QtAxis w(argc, argv);
    w.show();
    return a.exec();
}
