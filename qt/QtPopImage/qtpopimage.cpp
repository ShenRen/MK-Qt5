#include "qtpopimage.h"

#include <QtDebug>
#include <unistd.h>

QtPopImage::QtPopImage(int argc, char **argv, QWidget *parent) : QWidget(parent)
{
QString filename = argv[1];
QString Sdelay = argv[2];


    if(Sdelay.length())
	delay = Sdelay.toInt();

    if(!(delay < 10 && delay > 0 ))
	delay = 5;
    
    QLabel *label = new QLabel(this);
    QPixmap px(filename);

    label->setPixmap(px);
    resize(px.size());
    setGeometry(QStyle::alignedRect( Qt::LeftToRight, Qt::AlignCenter,
		size(), qApp->desktop()->availableGeometry() ) );

    setWindowFlags( Qt::FramelessWindowHint );

    QTimer::singleShot(delay * 1000, this, SLOT(onTimer()));
}

QtPopImage::~QtPopImage()
{
}


void QtPopImage::onTimer()
{

    exit(0);
}

////////////////////////////////////////////////////////////////////////////////////////////
