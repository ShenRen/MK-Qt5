#include "QtHalShow.h"
#include "Singleton.h"
#include <QtDebug>
#include <QMessageBox>


int main( int argc, char ** argv )
{
const QString str = "XL9PY644FG";

    Singleton sinst(str);
    if(!sinst.launch())
        {
        qDebug() << "\nThere is already an instance of 'HAL Configuration' running\n";
        return 0;
        }

    QApplication app(argc, argv);
    QtHalShow *d = new QtHalShow();
    d->exec();
    //return app.exec();
}
