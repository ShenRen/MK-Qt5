/********************************************************************************
** Form generated from reading UI file 'gremlinDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GREMLINDLG_H
#define UI_GREMLINDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_gremlinDlg
{
public:
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout_2;
    QLabel *label_5;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *leWidth;
    QLabel *label_2;
    QLineEdit *leHeight;
    QLabel *label_3;
    QLineEdit *leXoffset;
    QLabel *label_4;
    QLineEdit *leYoffset;
    QSpacerItem *horizontalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *gremlinDlg)
    {
        if (gremlinDlg->objectName().isEmpty())
            gremlinDlg->setObjectName(QStringLiteral("gremlinDlg"));
        gremlinDlg->resize(421, 239);
        gridLayout_3 = new QGridLayout(gremlinDlg);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_5 = new QLabel(gremlinDlg);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_2->addWidget(label_5, 0, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(gremlinDlg);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        leWidth = new QLineEdit(gremlinDlg);
        leWidth->setObjectName(QStringLiteral("leWidth"));

        gridLayout->addWidget(leWidth, 0, 1, 1, 2);

        label_2 = new QLabel(gremlinDlg);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 0, 3, 1, 1);

        leHeight = new QLineEdit(gremlinDlg);
        leHeight->setObjectName(QStringLiteral("leHeight"));

        gridLayout->addWidget(leHeight, 0, 4, 1, 1);

        label_3 = new QLabel(gremlinDlg);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 1, 0, 1, 2);

        leXoffset = new QLineEdit(gremlinDlg);
        leXoffset->setObjectName(QStringLiteral("leXoffset"));

        gridLayout->addWidget(leXoffset, 1, 2, 1, 1);

        label_4 = new QLabel(gremlinDlg);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 1, 3, 1, 1);

        leYoffset = new QLineEdit(gremlinDlg);
        leYoffset->setObjectName(QStringLiteral("leYoffset"));

        gridLayout->addWidget(leYoffset, 1, 4, 1, 1);

        horizontalSpacer = new QSpacerItem(198, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 2, 0, 1, 3);

        buttonBox = new QDialogButtonBox(gremlinDlg);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 2, 3, 1, 2);


        gridLayout_2->addLayout(gridLayout, 1, 0, 1, 1);


        gridLayout_3->addLayout(gridLayout_2, 0, 0, 1, 1);


        retranslateUi(gremlinDlg);
        QObject::connect(buttonBox, SIGNAL(rejected()), gremlinDlg, SLOT(reject()));

        QMetaObject::connectSlotsByName(gremlinDlg);
    } // setupUi

    void retranslateUi(QDialog *gremlinDlg)
    {
        gremlinDlg->setWindowTitle(QApplication::translate("gremlinDlg", "Gremlin Sizing", 0));
        label_5->setText(QApplication::translate("gremlinDlg", "The values set here will become active at next start-up.\n"
"Set the QtAxis window to the size and position required,\n"
" these dimensions will be remembered.\n"
"Then set the dimensions and offset for gremlin\n"
" to fill the remaining screen space.\n"
"Once set, it will be repeated thereafter.", 0));
        label->setText(QApplication::translate("gremlinDlg", "Width:", 0));
        label_2->setText(QApplication::translate("gremlinDlg", "Height:", 0));
        label_3->setText(QApplication::translate("gremlinDlg", "X Offset", 0));
        label_4->setText(QApplication::translate("gremlinDlg", "Y Offset", 0));
    } // retranslateUi

};

namespace Ui {
    class gremlinDlg: public Ui_gremlinDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GREMLINDLG_H
