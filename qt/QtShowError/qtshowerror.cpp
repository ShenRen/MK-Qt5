#include "qtshowerror.h"


QtShowError::QtShowError(int argc, char **argv, QWidget *parent) :  QDialog(parent)
{
QString str;
    setupUi(this);
    if(argc > 1)
	{
        str = argv[1];
	load(str, tb_print);
	if(argc > 2)
	// leave door open for extra args to set label text perhaps
	    {
	    str = argv[2];
	    load(str, tb_debug);
	    }
	else
	    {	    
	    tb_debug->hide();
	    l_debug->setText("Debug File Information: - None");
	    }
	}
    else
	{
	qDebug() << "\nUsage: qtshowerror printfile [debugfile]\n";
	exit(1);
	}
}


void QtShowError::load(QString& filename, QTextBrowser *browser)
{
QFile file(filename);
QString str;

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
        browser->setReadOnly(false);
        browser->clear();
        QTextStream in(&file);
        while (!in.atEnd())
            browser->append(in.readLine());
        file.close();
        browser->setReadOnly(true);
        }
    else
        qDebug() << "Error loading file " + filename ;
}