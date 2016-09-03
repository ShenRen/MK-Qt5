#include "qtpopimage.h"

int main( int argc, char ** argv )
{
    QApplication a( argc, argv );
    QtPopImage w(argc, argv);
    w.show();
    return a.exec();
}
