#include "XHCMonitorDialog.h"

int main( int argc, char ** argv )
{
//int x;
//    for(x = 0; x < argc; x++)
//	qDebug() << argv[x];

    QApplication app( argc, argv );
    XHCMonitorDialog *d = new XHCMonitorDialog(0, argc, argv);
    d->exec();
    //return app.exec();
}
