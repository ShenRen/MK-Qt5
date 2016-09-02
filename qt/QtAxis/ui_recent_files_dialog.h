/********************************************************************************
** Form generated from reading UI file 'recent_files_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RECENT_FILES_DIALOG_H
#define UI_RECENT_FILES_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_RecentFilesDialog
{
public:
    QGridLayout *gridLayout;
    QListWidget *listRecent;
    QSpacerItem *horizontalSpacer;
    QPushButton *pb_Cancel;
    QPushButton *pb_Open;

    void setupUi(QDialog *RecentFilesDialog)
    {
        if (RecentFilesDialog->objectName().isEmpty())
            RecentFilesDialog->setObjectName(QStringLiteral("RecentFilesDialog"));
        RecentFilesDialog->resize(471, 277);
        gridLayout = new QGridLayout(RecentFilesDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        listRecent = new QListWidget(RecentFilesDialog);
        listRecent->setObjectName(QStringLiteral("listRecent"));

        gridLayout->addWidget(listRecent, 0, 0, 1, 3);

        horizontalSpacer = new QSpacerItem(280, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 1);

        pb_Cancel = new QPushButton(RecentFilesDialog);
        pb_Cancel->setObjectName(QStringLiteral("pb_Cancel"));

        gridLayout->addWidget(pb_Cancel, 1, 1, 1, 1);

        pb_Open = new QPushButton(RecentFilesDialog);
        pb_Open->setObjectName(QStringLiteral("pb_Open"));

        gridLayout->addWidget(pb_Open, 1, 2, 1, 1);


        retranslateUi(RecentFilesDialog);
        QObject::connect(pb_Cancel, SIGNAL(clicked()), RecentFilesDialog, SLOT(reject()));
        QObject::connect(pb_Open, SIGNAL(clicked()), RecentFilesDialog, SLOT(onAcceptLocal()));
        QObject::connect(listRecent, SIGNAL(itemActivated(QListWidgetItem*)), RecentFilesDialog, SLOT(onSelected(QListWidgetItem*)));
        QObject::connect(listRecent, SIGNAL(itemClicked(QListWidgetItem*)), RecentFilesDialog, SLOT(onSelected(QListWidgetItem*)));
        QObject::connect(listRecent, SIGNAL(itemPressed(QListWidgetItem*)), RecentFilesDialog, SLOT(onSelected(QListWidgetItem*)));
        QObject::connect(listRecent, SIGNAL(doubleClicked(QModelIndex)), RecentFilesDialog, SLOT(onAcceptLocal()));

        QMetaObject::connectSlotsByName(RecentFilesDialog);
    } // setupUi

    void retranslateUi(QDialog *RecentFilesDialog)
    {
        RecentFilesDialog->setWindowTitle(QApplication::translate("RecentFilesDialog", "Recent Files", 0));
        pb_Cancel->setText(QApplication::translate("RecentFilesDialog", "Cancel", 0));
        pb_Open->setText(QApplication::translate("RecentFilesDialog", "Open", 0));
    } // retranslateUi

};

namespace Ui {
    class RecentFilesDialog: public Ui_RecentFilesDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECENT_FILES_DIALOG_H
