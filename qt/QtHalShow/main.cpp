#include "QtHalShow.h"
#include "RunGuard.h"
#include <QtDebug>
#include <QMessageBox>


int main( int argc, char ** argv )
{
    RunGuard guard("XL9PY644FG" );
    if ( !guard.tryToRun() )
        {
        qDebug() << "\nThere is already an instance of 'HAL Configuration' running\n";
        return 0;
        }

    QApplication app( argc, argv );
    QtHalShow *d = new QtHalShow();
    d->exec();
    //return app.exec();
}
