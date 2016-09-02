#include "touch-off_dlg.h"

#include <QtDebug>



touchOffDialog::touchOffDialog(QWidget *parent, QStringList& list, char axis)
:QDialog(parent)
{
QString str;

    // build the dialog from ui
    setupUi(this);
    le_value->setText("0");
    cb_coordinate->insertItems(0, list);
    str.sprintf("%c Axis Value:-", axis);
    label->setText(str);
}

void touchOffDialog::onActivated(QString string)
{
    cbText = string;
}


void touchOffDialog::onAccept()
{
    value = (le_value->text()).toFloat();
    if(!cbText.length())
        cbText = cb_coordinate->currentText();
    index = cb_coordinate->currentIndex();
    QDialog::accept();
}


