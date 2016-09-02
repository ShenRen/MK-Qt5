/********************************************************************************
** Form generated from reading UI file 'touch-off_dlg.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TOUCH_2D_OFF_DLG_H
#define UI_TOUCH_2D_OFF_DLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_TouchOffDlg
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QLineEdit *le_value;
    QLabel *label_2;
    QComboBox *cb_coordinate;

    void setupUi(QDialog *TouchOffDlg)
    {
        if (TouchOffDlg->objectName().isEmpty())
            TouchOffDlg->setObjectName(QStringLiteral("TouchOffDlg"));
        TouchOffDlg->resize(332, 175);
        buttonBox = new QDialogButtonBox(TouchOffDlg);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(30, 110, 191, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label = new QLabel(TouchOffDlg);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 20, 111, 31));
        le_value = new QLineEdit(TouchOffDlg);
        le_value->setObjectName(QStringLiteral("le_value"));
        le_value->setGeometry(QRect(170, 30, 113, 22));
        label_2 = new QLabel(TouchOffDlg);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 70, 141, 21));
        cb_coordinate = new QComboBox(TouchOffDlg);
        cb_coordinate->setObjectName(QStringLiteral("cb_coordinate"));
        cb_coordinate->setGeometry(QRect(170, 70, 111, 22));

        retranslateUi(TouchOffDlg);
        QObject::connect(buttonBox, SIGNAL(rejected()), TouchOffDlg, SLOT(reject()));
        QObject::connect(cb_coordinate, SIGNAL(activated(QString)), TouchOffDlg, SLOT(onActivated(QString)));
        QObject::connect(buttonBox, SIGNAL(accepted()), TouchOffDlg, SLOT(onAccept()));

        QMetaObject::connectSlotsByName(TouchOffDlg);
    } // setupUi

    void retranslateUi(QDialog *TouchOffDlg)
    {
        TouchOffDlg->setWindowTitle(QApplication::translate("TouchOffDlg", "Tool Touch Off", 0));
        label->setText(QApplication::translate("TouchOffDlg", "Axis value:-", 0));
        label_2->setText(QApplication::translate("TouchOffDlg", "Coordinate System:-", 0));
    } // retranslateUi

};

namespace Ui {
    class TouchOffDlg: public Ui_TouchOffDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TOUCH_2D_OFF_DLG_H
