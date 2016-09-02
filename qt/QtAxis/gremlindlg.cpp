#include "gremlindlg.h"

#include <QtDebug>


gremlinDlg::gremlinDlg(QWidget *parent, int w, int h, int x, int y)
:QDialog(parent)
{
QString str;
    // build the dialog from ui
    setupUi(this);
    width = w;
    height = h;
    xoffset = x;
    yoffset = y;
    leWidth->setText(str.sprintf("%d", width));
    leHeight->setText(str.sprintf("%d", height));
    leXoffset->setText(str.sprintf("%d", xoffset));
    leYoffset->setText(str.sprintf("%d", yoffset));
//    qDebug() << "In dlg " << width << height;
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(onAccept()));
}


void gremlinDlg::onAccept()
{
    width = (leWidth->text()).toInt();
    height = (leHeight->text()).toInt();
    xoffset = (leXoffset->text()).toInt();
    yoffset = (leYoffset->text()).toInt();
//    qDebug() << "In dlg " << (leWidth->text()).toInt() << (leHeight->text()).toInt() << (leXoffset->text()).toInt() << (leYoffset->text()).toInt();
    QDialog::accept();
}


