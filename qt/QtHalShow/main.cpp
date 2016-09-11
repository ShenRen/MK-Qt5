#include "QtHalShow.h"

// TODO
// see if the app can be just hidden on any close method
// then if invoked again, just show()
// Will need to walk a list of current Qt processes?

int main( int argc, char ** argv )
{
    QApplication app( argc, argv );
    QtHalShow *d = new QtHalShow();
    d->exec();
    //return app.exec();
}
