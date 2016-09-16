#include "XHCMonitorDialog.h"

int main( int argc, char ** argv )
{
const QString str = "8PBQ65GHY9";

    Singleton sinst(str);
    if(!sinst.launch())
        {
        qDebug() << "\nThere is already an instance of 'QtXHCMonitor' running\n";
        return 0;
        }

    QApplication app( argc, argv );
    XHCMonitorDialog *d = new XHCMonitorDialog(0, argc, argv);
    d->exec();
}
