/********************************************************************************
** Form generated from reading UI file 'chooser.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHOOSER_H
#define UI_CHOOSER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTreeWidget>

QT_BEGIN_NAMESPACE

class Ui_ChooserDlg
{
public:
    QGridLayout *gridLayout;
    QDialogButtonBox *buttonBox;
    QTreeWidget *treeConfigs;
    QTextBrowser *tbReadme;
    QLabel *label;
    QLabel *label_2;
    QLabel *pathLabel;

    void setupUi(QDialog *ChooserDlg)
    {
        if (ChooserDlg->objectName().isEmpty())
            ChooserDlg->setObjectName(QStringLiteral("ChooserDlg"));
        ChooserDlg->resize(886, 745);
        gridLayout = new QGridLayout(ChooserDlg);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        buttonBox = new QDialogButtonBox(ChooserDlg);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 2, 2, 1, 1);

        treeConfigs = new QTreeWidget(ChooserDlg);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treeConfigs->setHeaderItem(__qtreewidgetitem);
        treeConfigs->setObjectName(QStringLiteral("treeConfigs"));

        gridLayout->addWidget(treeConfigs, 0, 0, 2, 1);

        tbReadme = new QTextBrowser(ChooserDlg);
        tbReadme->setObjectName(QStringLiteral("tbReadme"));

        gridLayout->addWidget(tbReadme, 1, 1, 1, 2);

        label = new QLabel(ChooserDlg);
        label->setObjectName(QStringLiteral("label"));
        label->setPixmap(QPixmap(QString::fromUtf8(":/newPrefix/machinekiticon.png")));
        label->setScaledContents(true);

        gridLayout->addWidget(label, 0, 1, 1, 1);

        label_2 = new QLabel(ChooserDlg);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 0, 2, 1, 1);

        pathLabel = new QLabel(ChooserDlg);
        pathLabel->setObjectName(QStringLiteral("pathLabel"));

        gridLayout->addWidget(pathLabel, 2, 0, 1, 2);


        retranslateUi(ChooserDlg);
        QObject::connect(buttonBox, SIGNAL(accepted()), ChooserDlg, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ChooserDlg, SLOT(reject()));

        QMetaObject::connectSlotsByName(ChooserDlg);
    } // setupUi

    void retranslateUi(QDialog *ChooserDlg)
    {
        ChooserDlg->setWindowTitle(QApplication::translate("ChooserDlg", "Machinekit - Configuration Chooser", 0));
        label->setText(QString());
        label_2->setText(QApplication::translate("ChooserDlg", "<html><head/><body><p align=\"center\"><span style=\" font-size:18pt; font-weight:600;\">Machinekit.</span></p><p align=\"center\"><span style=\" font-size:16pt;\">Moves.</span></p><p align=\"center\"><span style=\" font-size:16pt;\">Controls.</span></p><p align=\"center\"><span style=\" font-size:16pt;\">Things.</span></p></body></html>", 0));
        pathLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ChooserDlg: public Ui_ChooserDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHOOSER_H
