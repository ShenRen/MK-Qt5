/********************************************************************************
** Form generated from reading UI file 'axis.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AXIS_H
#define UI_AXIS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "code_editor.h"

QT_BEGIN_NAMESPACE

class Ui_QtAxis
{
public:
    QAction *actionExit;
    QAction *actionOpen;
    QAction *actionRecentFiles;
    QAction *actionEdit;
    QAction *actionReload;
    QAction *actionProperties;
    QAction *actionSaveAs;
    QAction *actionToolTable;
    QAction *actionReloadToolTable;
    QAction *actionToggleEstop;
    QAction *actionToggleMachineOn;
    QAction *actionRunProgram;
    QAction *actionPauseProgram;
    QAction *actionStopProgram;
    QAction *actionStep;
    QAction *actionAboutQtAxis;
    QAction *actionAboutQt;
    QAction *actionHome;
    QAction *actionLoadLast;
    QAction *actionOptionalStop;
    QAction *actionRun;
    QAction *actionGremlin;
    QAction *actionStopOnError;
    QAction *action_Reload;
    QWidget *centralwidget;
    QGridLayout *gridLayout_6;
    QTabWidget *tabControl;
    QWidget *tabManual;
    QGridLayout *gridLayout_7;
    QHBoxLayout *horizontalLayout_5;
    QRadioButton *rbX;
    QRadioButton *rbY;
    QRadioButton *rbZ;
    QRadioButton *rbU;
    QRadioButton *rbV;
    QRadioButton *rbW;
    QRadioButton *rbA;
    QRadioButton *rbB;
    QRadioButton *rbC;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pbHome;
    QPushButton *pbUnReHome;
    QPushButton *pbTouch;
    QHBoxLayout *horizontalLayout_3;
    QLabel *lbFeed;
    QSlider *slideFeed;
    QHBoxLayout *horizontalLayout_2;
    QLabel *lbVelocity;
    QSlider *slideVelocity;
    QGridLayout *gridLayout_5;
    QPushButton *pbJogYPlus;
    QPushButton *pbJogXPlus;
    QPushButton *pbJogXMinus;
    QPushButton *pbJogZPlus;
    QPushButton *pbJogZMinus;
    QPushButton *pbJogYMinus;
    QHBoxLayout *horizontalLayout;
    QLabel *lbJog;
    QSlider *slideJog;
    QWidget *tabMDI;
    QGridLayout *gridLayout_3;
    QListWidget *list_MDI;
    QLineEdit *le_MDI;
    QPushButton *pb_MDI;
    QLabel *lb_activeGCodes;
    QLabel *lb_activeMCodes;
    QLabel *lb_feedSpeed;
    QPushButton *pb_MDIClear;
    QPushButton *pb_MDICopy;
    QPushButton *pb_MDIPaste;
    QTabWidget *tabView;
    QWidget *tabPlot;
    QGridLayout *gridLayout_2;
    QTextBrowser *te_Messages;
    QPushButton *pbClear;
    QSpacerItem *horizontalSpacer;
    QWidget *tabDRO;
    QGridLayout *gridLayout_4;
    QSpacerItem *verticalSpacer;
    QLabel *lbHeaderG54;
    QLabel *lbHeaderG53;
    QLabel *lbHeaderx;
    QLabel *labelX;
    QLabel *lbXG54;
    QLabel *lbXG53;
    QLabel *lbXx;
    QLabel *labelY;
    QLabel *lbYG54;
    QLabel *lbYG53;
    QLabel *lbYx;
    QLabel *labelZ;
    QLabel *lbZG54;
    QLabel *lbZG53;
    QLabel *lbZx;
    QLabel *labelU;
    QLabel *lbUG54;
    QLabel *lbUG53;
    QLabel *lbUx;
    QLabel *labelV;
    QLabel *lbVG54;
    QLabel *lbVG53;
    QLabel *lbVx;
    QLabel *labelW;
    QLabel *lbWG54;
    QLabel *lbWG53;
    QLabel *lbWx;
    QLabel *labelA;
    QLabel *lbAG54;
    QLabel *lbAG53;
    QLabel *lbAx;
    QLabel *labelB;
    QLabel *lbBG54;
    QLabel *lbBG53;
    QLabel *lbBx;
    QLabel *labelC;
    QLabel *lbCG54;
    QLabel *lbCG53;
    QLabel *lbCx;
    QWidget *tab;
    QGridLayout *gridLayout;
    CodeEditor *te_Code;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuMachine;
    QMenu *menuHelp;
    QMenu *menuVeiw;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *QtAxis)
    {
        if (QtAxis->objectName().isEmpty())
            QtAxis->setObjectName(QStringLiteral("QtAxis"));
        QtAxis->resize(606, 925);
        actionExit = new QAction(QtAxis);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/new/CNCicons/icons/exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExit->setIcon(icon);
        actionOpen = new QAction(QtAxis);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/new/CNCicons/icons/fileopen.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon1);
        actionRecentFiles = new QAction(QtAxis);
        actionRecentFiles->setObjectName(QStringLiteral("actionRecentFiles"));
        actionEdit = new QAction(QtAxis);
        actionEdit->setObjectName(QStringLiteral("actionEdit"));
        actionReload = new QAction(QtAxis);
        actionReload->setObjectName(QStringLiteral("actionReload"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/new/CNCicons/icons/reload.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionReload->setIcon(icon2);
        actionProperties = new QAction(QtAxis);
        actionProperties->setObjectName(QStringLiteral("actionProperties"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/new/CNCicons/icons/properties.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionProperties->setIcon(icon3);
        actionSaveAs = new QAction(QtAxis);
        actionSaveAs->setObjectName(QStringLiteral("actionSaveAs"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/new/CNCicons/icons/filesaveas.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSaveAs->setIcon(icon4);
        actionToolTable = new QAction(QtAxis);
        actionToolTable->setObjectName(QStringLiteral("actionToolTable"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/new/CNCicons/icons/edit.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionToolTable->setIcon(icon5);
        actionReloadToolTable = new QAction(QtAxis);
        actionReloadToolTable->setObjectName(QStringLiteral("actionReloadToolTable"));
        actionToggleEstop = new QAction(QtAxis);
        actionToggleEstop->setObjectName(QStringLiteral("actionToggleEstop"));
        actionToggleEstop->setCheckable(true);
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/new/CNCicons/icons/estop.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionToggleEstop->setIcon(icon6);
        actionToggleMachineOn = new QAction(QtAxis);
        actionToggleMachineOn->setObjectName(QStringLiteral("actionToggleMachineOn"));
        actionToggleMachineOn->setCheckable(true);
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/new/CNCicons/icons/machine_toggle.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionToggleMachineOn->setIcon(icon7);
        actionRunProgram = new QAction(QtAxis);
        actionRunProgram->setObjectName(QStringLiteral("actionRunProgram"));
        actionRunProgram->setCheckable(true);
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/new/CNCicons/icons/run_program.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRunProgram->setIcon(icon8);
        actionPauseProgram = new QAction(QtAxis);
        actionPauseProgram->setObjectName(QStringLiteral("actionPauseProgram"));
        actionPauseProgram->setCheckable(true);
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/new/CNCicons/icons/pause_program.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPauseProgram->setIcon(icon9);
        actionStopProgram = new QAction(QtAxis);
        actionStopProgram->setObjectName(QStringLiteral("actionStopProgram"));
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/new/CNCicons/icons/stop_program.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionStopProgram->setIcon(icon10);
        actionStep = new QAction(QtAxis);
        actionStep->setObjectName(QStringLiteral("actionStep"));
        QIcon icon11;
        icon11.addFile(QStringLiteral(":/new/CNCicons/icons/skip_program.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionStep->setIcon(icon11);
        actionAboutQtAxis = new QAction(QtAxis);
        actionAboutQtAxis->setObjectName(QStringLiteral("actionAboutQtAxis"));
        QIcon icon12;
        icon12.addFile(QStringLiteral(":/new/CNCicons/icons/help_about.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAboutQtAxis->setIcon(icon12);
        actionAboutQt = new QAction(QtAxis);
        actionAboutQt->setObjectName(QStringLiteral("actionAboutQt"));
        QIcon icon13;
        icon13.addFile(QStringLiteral(":/new/CNCicons/icons/Qt.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAboutQt->setIcon(icon13);
        actionHome = new QAction(QtAxis);
        actionHome->setObjectName(QStringLiteral("actionHome"));
        QIcon icon14;
        icon14.addFile(QStringLiteral(":/new/CNCicons/icons/kfm_home.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionHome->setIcon(icon14);
        actionLoadLast = new QAction(QtAxis);
        actionLoadLast->setObjectName(QStringLiteral("actionLoadLast"));
        actionOptionalStop = new QAction(QtAxis);
        actionOptionalStop->setObjectName(QStringLiteral("actionOptionalStop"));
        actionOptionalStop->setCheckable(true);
        QIcon icon15;
        icon15.addFile(QStringLiteral(":/new/CNCicons/icons/optional.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOptionalStop->setIcon(icon15);
        actionRun = new QAction(QtAxis);
        actionRun->setObjectName(QStringLiteral("actionRun"));
        actionGremlin = new QAction(QtAxis);
        actionGremlin->setObjectName(QStringLiteral("actionGremlin"));
        actionGremlin->setCheckable(false);
        actionGremlin->setEnabled(true);
        actionStopOnError = new QAction(QtAxis);
        actionStopOnError->setObjectName(QStringLiteral("actionStopOnError"));
        actionStopOnError->setCheckable(true);
        action_Reload = new QAction(QtAxis);
        action_Reload->setObjectName(QStringLiteral("action_Reload"));
        centralwidget = new QWidget(QtAxis);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout_6 = new QGridLayout(centralwidget);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        tabControl = new QTabWidget(centralwidget);
        tabControl->setObjectName(QStringLiteral("tabControl"));
        tabManual = new QWidget();
        tabManual->setObjectName(QStringLiteral("tabManual"));
        gridLayout_7 = new QGridLayout(tabManual);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        rbX = new QRadioButton(tabManual);
        rbX->setObjectName(QStringLiteral("rbX"));

        horizontalLayout_5->addWidget(rbX);

        rbY = new QRadioButton(tabManual);
        rbY->setObjectName(QStringLiteral("rbY"));

        horizontalLayout_5->addWidget(rbY);

        rbZ = new QRadioButton(tabManual);
        rbZ->setObjectName(QStringLiteral("rbZ"));

        horizontalLayout_5->addWidget(rbZ);

        rbU = new QRadioButton(tabManual);
        rbU->setObjectName(QStringLiteral("rbU"));

        horizontalLayout_5->addWidget(rbU);

        rbV = new QRadioButton(tabManual);
        rbV->setObjectName(QStringLiteral("rbV"));

        horizontalLayout_5->addWidget(rbV);

        rbW = new QRadioButton(tabManual);
        rbW->setObjectName(QStringLiteral("rbW"));

        horizontalLayout_5->addWidget(rbW);

        rbA = new QRadioButton(tabManual);
        rbA->setObjectName(QStringLiteral("rbA"));

        horizontalLayout_5->addWidget(rbA);

        rbB = new QRadioButton(tabManual);
        rbB->setObjectName(QStringLiteral("rbB"));

        horizontalLayout_5->addWidget(rbB);

        rbC = new QRadioButton(tabManual);
        rbC->setObjectName(QStringLiteral("rbC"));

        horizontalLayout_5->addWidget(rbC);


        gridLayout_7->addLayout(horizontalLayout_5, 0, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        pbHome = new QPushButton(tabManual);
        pbHome->setObjectName(QStringLiteral("pbHome"));

        horizontalLayout_4->addWidget(pbHome);

        pbUnReHome = new QPushButton(tabManual);
        pbUnReHome->setObjectName(QStringLiteral("pbUnReHome"));

        horizontalLayout_4->addWidget(pbUnReHome);

        pbTouch = new QPushButton(tabManual);
        pbTouch->setObjectName(QStringLiteral("pbTouch"));

        horizontalLayout_4->addWidget(pbTouch);


        gridLayout_7->addLayout(horizontalLayout_4, 1, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        lbFeed = new QLabel(tabManual);
        lbFeed->setObjectName(QStringLiteral("lbFeed"));

        horizontalLayout_3->addWidget(lbFeed);

        slideFeed = new QSlider(tabManual);
        slideFeed->setObjectName(QStringLiteral("slideFeed"));
        slideFeed->setMaximum(150);
        slideFeed->setSingleStep(5);
        slideFeed->setPageStep(20);
        slideFeed->setValue(100);
        slideFeed->setOrientation(Qt::Horizontal);
        slideFeed->setTickPosition(QSlider::TicksBelow);
        slideFeed->setTickInterval(10);

        horizontalLayout_3->addWidget(slideFeed);


        gridLayout_7->addLayout(horizontalLayout_3, 2, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        lbVelocity = new QLabel(tabManual);
        lbVelocity->setObjectName(QStringLiteral("lbVelocity"));

        horizontalLayout_2->addWidget(lbVelocity);

        slideVelocity = new QSlider(tabManual);
        slideVelocity->setObjectName(QStringLiteral("slideVelocity"));
        slideVelocity->setMaximum(2000);
        slideVelocity->setSingleStep(10);
        slideVelocity->setPageStep(50);
        slideVelocity->setValue(200);
        slideVelocity->setTracking(true);
        slideVelocity->setOrientation(Qt::Horizontal);
        slideVelocity->setInvertedAppearance(false);
        slideVelocity->setInvertedControls(false);
        slideVelocity->setTickPosition(QSlider::TicksBelow);
        slideVelocity->setTickInterval(100);

        horizontalLayout_2->addWidget(slideVelocity);


        gridLayout_7->addLayout(horizontalLayout_2, 3, 0, 1, 1);

        gridLayout_5 = new QGridLayout();
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        pbJogYPlus = new QPushButton(tabManual);
        pbJogYPlus->setObjectName(QStringLiteral("pbJogYPlus"));

        gridLayout_5->addWidget(pbJogYPlus, 0, 1, 1, 1);

        pbJogXPlus = new QPushButton(tabManual);
        pbJogXPlus->setObjectName(QStringLiteral("pbJogXPlus"));
        pbJogXPlus->setAutoRepeat(false);
        pbJogXPlus->setAutoExclusive(false);

        gridLayout_5->addWidget(pbJogXPlus, 1, 2, 1, 1);

        pbJogXMinus = new QPushButton(tabManual);
        pbJogXMinus->setObjectName(QStringLiteral("pbJogXMinus"));
        pbJogXMinus->setAutoRepeat(false);

        gridLayout_5->addWidget(pbJogXMinus, 1, 0, 1, 1);

        pbJogZPlus = new QPushButton(tabManual);
        pbJogZPlus->setObjectName(QStringLiteral("pbJogZPlus"));

        gridLayout_5->addWidget(pbJogZPlus, 0, 3, 1, 1);

        pbJogZMinus = new QPushButton(tabManual);
        pbJogZMinus->setObjectName(QStringLiteral("pbJogZMinus"));

        gridLayout_5->addWidget(pbJogZMinus, 2, 3, 1, 1);

        pbJogYMinus = new QPushButton(tabManual);
        pbJogYMinus->setObjectName(QStringLiteral("pbJogYMinus"));

        gridLayout_5->addWidget(pbJogYMinus, 2, 1, 1, 1);


        gridLayout_7->addLayout(gridLayout_5, 4, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        lbJog = new QLabel(tabManual);
        lbJog->setObjectName(QStringLiteral("lbJog"));

        horizontalLayout->addWidget(lbJog);

        slideJog = new QSlider(tabManual);
        slideJog->setObjectName(QStringLiteral("slideJog"));
        slideJog->setMaximum(600);
        slideJog->setSingleStep(10);
        slideJog->setPageStep(50);
        slideJog->setValue(300);
        slideJog->setSliderPosition(300);
        slideJog->setOrientation(Qt::Horizontal);
        slideJog->setTickPosition(QSlider::TicksBelow);
        slideJog->setTickInterval(50);

        horizontalLayout->addWidget(slideJog);


        gridLayout_7->addLayout(horizontalLayout, 5, 0, 1, 1);

        tabControl->addTab(tabManual, QString());
        tabMDI = new QWidget();
        tabMDI->setObjectName(QStringLiteral("tabMDI"));
        gridLayout_3 = new QGridLayout(tabMDI);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        list_MDI = new QListWidget(tabMDI);
        list_MDI->setObjectName(QStringLiteral("list_MDI"));
        list_MDI->setEditTriggers(QAbstractItemView::NoEditTriggers);
        list_MDI->setAlternatingRowColors(true);

        gridLayout_3->addWidget(list_MDI, 0, 0, 1, 4);

        le_MDI = new QLineEdit(tabMDI);
        le_MDI->setObjectName(QStringLiteral("le_MDI"));

        gridLayout_3->addWidget(le_MDI, 1, 0, 1, 3);

        pb_MDI = new QPushButton(tabMDI);
        pb_MDI->setObjectName(QStringLiteral("pb_MDI"));

        gridLayout_3->addWidget(pb_MDI, 1, 3, 1, 1);

        lb_activeGCodes = new QLabel(tabMDI);
        lb_activeGCodes->setObjectName(QStringLiteral("lb_activeGCodes"));
        lb_activeGCodes->setFrameShape(QFrame::StyledPanel);
        lb_activeGCodes->setFrameShadow(QFrame::Sunken);
        lb_activeGCodes->setLineWidth(2);

        gridLayout_3->addWidget(lb_activeGCodes, 2, 0, 1, 4);

        lb_activeMCodes = new QLabel(tabMDI);
        lb_activeMCodes->setObjectName(QStringLiteral("lb_activeMCodes"));
        lb_activeMCodes->setFrameShape(QFrame::StyledPanel);
        lb_activeMCodes->setFrameShadow(QFrame::Sunken);
        lb_activeMCodes->setLineWidth(2);

        gridLayout_3->addWidget(lb_activeMCodes, 3, 0, 1, 4);

        lb_feedSpeed = new QLabel(tabMDI);
        lb_feedSpeed->setObjectName(QStringLiteral("lb_feedSpeed"));
        lb_feedSpeed->setFrameShape(QFrame::StyledPanel);
        lb_feedSpeed->setFrameShadow(QFrame::Sunken);
        lb_feedSpeed->setLineWidth(2);

        gridLayout_3->addWidget(lb_feedSpeed, 4, 0, 1, 1);

        pb_MDIClear = new QPushButton(tabMDI);
        pb_MDIClear->setObjectName(QStringLiteral("pb_MDIClear"));

        gridLayout_3->addWidget(pb_MDIClear, 4, 1, 1, 1);

        pb_MDICopy = new QPushButton(tabMDI);
        pb_MDICopy->setObjectName(QStringLiteral("pb_MDICopy"));

        gridLayout_3->addWidget(pb_MDICopy, 4, 2, 1, 1);

        pb_MDIPaste = new QPushButton(tabMDI);
        pb_MDIPaste->setObjectName(QStringLiteral("pb_MDIPaste"));

        gridLayout_3->addWidget(pb_MDIPaste, 4, 3, 1, 1);

        tabControl->addTab(tabMDI, QString());

        gridLayout_6->addWidget(tabControl, 0, 0, 1, 1);

        tabView = new QTabWidget(centralwidget);
        tabView->setObjectName(QStringLiteral("tabView"));
        tabPlot = new QWidget();
        tabPlot->setObjectName(QStringLiteral("tabPlot"));
        gridLayout_2 = new QGridLayout(tabPlot);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        te_Messages = new QTextBrowser(tabPlot);
        te_Messages->setObjectName(QStringLiteral("te_Messages"));

        gridLayout_2->addWidget(te_Messages, 0, 0, 1, 2);

        pbClear = new QPushButton(tabPlot);
        pbClear->setObjectName(QStringLiteral("pbClear"));

        gridLayout_2->addWidget(pbClear, 1, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(407, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 1, 1, 1, 1);

        tabView->addTab(tabPlot, QString());
        tabDRO = new QWidget();
        tabDRO->setObjectName(QStringLiteral("tabDRO"));
        gridLayout_4 = new QGridLayout(tabDRO);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        verticalSpacer = new QSpacerItem(20, 42, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_4->addItem(verticalSpacer, 0, 0, 1, 1);

        lbHeaderG54 = new QLabel(tabDRO);
        lbHeaderG54->setObjectName(QStringLiteral("lbHeaderG54"));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        lbHeaderG54->setFont(font);
        lbHeaderG54->setFrameShape(QFrame::Box);

        gridLayout_4->addWidget(lbHeaderG54, 0, 1, 1, 1);

        lbHeaderG53 = new QLabel(tabDRO);
        lbHeaderG53->setObjectName(QStringLiteral("lbHeaderG53"));
        lbHeaderG53->setFont(font);
        lbHeaderG53->setFrameShape(QFrame::Box);

        gridLayout_4->addWidget(lbHeaderG53, 0, 2, 1, 1);

        lbHeaderx = new QLabel(tabDRO);
        lbHeaderx->setObjectName(QStringLiteral("lbHeaderx"));
        lbHeaderx->setFont(font);
        lbHeaderx->setFrameShape(QFrame::Box);

        gridLayout_4->addWidget(lbHeaderx, 0, 3, 1, 1);

        labelX = new QLabel(tabDRO);
        labelX->setObjectName(QStringLiteral("labelX"));
        labelX->setFont(font);
        labelX->setScaledContents(true);

        gridLayout_4->addWidget(labelX, 1, 0, 1, 1);

        lbXG54 = new QLabel(tabDRO);
        lbXG54->setObjectName(QStringLiteral("lbXG54"));
        lbXG54->setFrameShape(QFrame::Box);

        gridLayout_4->addWidget(lbXG54, 1, 1, 1, 1);

        lbXG53 = new QLabel(tabDRO);
        lbXG53->setObjectName(QStringLiteral("lbXG53"));
        lbXG53->setFrameShape(QFrame::Box);

        gridLayout_4->addWidget(lbXG53, 1, 2, 1, 1);

        lbXx = new QLabel(tabDRO);
        lbXx->setObjectName(QStringLiteral("lbXx"));
        lbXx->setFrameShape(QFrame::Box);

        gridLayout_4->addWidget(lbXx, 1, 3, 1, 1);

        labelY = new QLabel(tabDRO);
        labelY->setObjectName(QStringLiteral("labelY"));
        labelY->setFont(font);
        labelY->setScaledContents(true);

        gridLayout_4->addWidget(labelY, 2, 0, 1, 1);

        lbYG54 = new QLabel(tabDRO);
        lbYG54->setObjectName(QStringLiteral("lbYG54"));
        lbYG54->setFrameShape(QFrame::Box);

        gridLayout_4->addWidget(lbYG54, 2, 1, 1, 1);

        lbYG53 = new QLabel(tabDRO);
        lbYG53->setObjectName(QStringLiteral("lbYG53"));
        lbYG53->setFrameShape(QFrame::Box);

        gridLayout_4->addWidget(lbYG53, 2, 2, 1, 1);

        lbYx = new QLabel(tabDRO);
        lbYx->setObjectName(QStringLiteral("lbYx"));
        lbYx->setFrameShape(QFrame::Box);

        gridLayout_4->addWidget(lbYx, 2, 3, 1, 1);

        labelZ = new QLabel(tabDRO);
        labelZ->setObjectName(QStringLiteral("labelZ"));
        labelZ->setFont(font);
        labelZ->setScaledContents(true);

        gridLayout_4->addWidget(labelZ, 3, 0, 1, 1);

        lbZG54 = new QLabel(tabDRO);
        lbZG54->setObjectName(QStringLiteral("lbZG54"));
        lbZG54->setFrameShape(QFrame::Box);

        gridLayout_4->addWidget(lbZG54, 3, 1, 1, 1);

        lbZG53 = new QLabel(tabDRO);
        lbZG53->setObjectName(QStringLiteral("lbZG53"));
        lbZG53->setFrameShape(QFrame::Box);

        gridLayout_4->addWidget(lbZG53, 3, 2, 1, 1);

        lbZx = new QLabel(tabDRO);
        lbZx->setObjectName(QStringLiteral("lbZx"));
        lbZx->setFrameShape(QFrame::Box);

        gridLayout_4->addWidget(lbZx, 3, 3, 1, 1);

        labelU = new QLabel(tabDRO);
        labelU->setObjectName(QStringLiteral("labelU"));
        labelU->setFont(font);
        labelU->setScaledContents(true);

        gridLayout_4->addWidget(labelU, 4, 0, 1, 1);

        lbUG54 = new QLabel(tabDRO);
        lbUG54->setObjectName(QStringLiteral("lbUG54"));
        lbUG54->setFrameShape(QFrame::Box);

        gridLayout_4->addWidget(lbUG54, 4, 1, 1, 1);

        lbUG53 = new QLabel(tabDRO);
        lbUG53->setObjectName(QStringLiteral("lbUG53"));
        lbUG53->setFrameShape(QFrame::Box);

        gridLayout_4->addWidget(lbUG53, 4, 2, 1, 1);

        lbUx = new QLabel(tabDRO);
        lbUx->setObjectName(QStringLiteral("lbUx"));
        lbUx->setFrameShape(QFrame::Box);

        gridLayout_4->addWidget(lbUx, 4, 3, 1, 1);

        labelV = new QLabel(tabDRO);
        labelV->setObjectName(QStringLiteral("labelV"));
        labelV->setFont(font);
        labelV->setScaledContents(true);

        gridLayout_4->addWidget(labelV, 5, 0, 1, 1);

        lbVG54 = new QLabel(tabDRO);
        lbVG54->setObjectName(QStringLiteral("lbVG54"));
        lbVG54->setFrameShape(QFrame::Box);

        gridLayout_4->addWidget(lbVG54, 5, 1, 1, 1);

        lbVG53 = new QLabel(tabDRO);
        lbVG53->setObjectName(QStringLiteral("lbVG53"));
        lbVG53->setFrameShape(QFrame::Box);

        gridLayout_4->addWidget(lbVG53, 5, 2, 1, 1);

        lbVx = new QLabel(tabDRO);
        lbVx->setObjectName(QStringLiteral("lbVx"));
        lbVx->setFrameShape(QFrame::Box);

        gridLayout_4->addWidget(lbVx, 5, 3, 1, 1);

        labelW = new QLabel(tabDRO);
        labelW->setObjectName(QStringLiteral("labelW"));
        labelW->setFont(font);
        labelW->setScaledContents(true);

        gridLayout_4->addWidget(labelW, 6, 0, 1, 1);

        lbWG54 = new QLabel(tabDRO);
        lbWG54->setObjectName(QStringLiteral("lbWG54"));
        lbWG54->setFrameShape(QFrame::Box);

        gridLayout_4->addWidget(lbWG54, 6, 1, 1, 1);

        lbWG53 = new QLabel(tabDRO);
        lbWG53->setObjectName(QStringLiteral("lbWG53"));
        lbWG53->setFrameShape(QFrame::Box);

        gridLayout_4->addWidget(lbWG53, 6, 2, 1, 1);

        lbWx = new QLabel(tabDRO);
        lbWx->setObjectName(QStringLiteral("lbWx"));
        lbWx->setFrameShape(QFrame::Box);

        gridLayout_4->addWidget(lbWx, 6, 3, 1, 1);

        labelA = new QLabel(tabDRO);
        labelA->setObjectName(QStringLiteral("labelA"));
        labelA->setFont(font);
        labelA->setScaledContents(true);

        gridLayout_4->addWidget(labelA, 7, 0, 1, 1);

        lbAG54 = new QLabel(tabDRO);
        lbAG54->setObjectName(QStringLiteral("lbAG54"));
        lbAG54->setFrameShape(QFrame::Box);

        gridLayout_4->addWidget(lbAG54, 7, 1, 1, 1);

        lbAG53 = new QLabel(tabDRO);
        lbAG53->setObjectName(QStringLiteral("lbAG53"));
        lbAG53->setFrameShape(QFrame::Box);

        gridLayout_4->addWidget(lbAG53, 7, 2, 1, 1);

        lbAx = new QLabel(tabDRO);
        lbAx->setObjectName(QStringLiteral("lbAx"));
        lbAx->setFrameShape(QFrame::Box);

        gridLayout_4->addWidget(lbAx, 7, 3, 1, 1);

        labelB = new QLabel(tabDRO);
        labelB->setObjectName(QStringLiteral("labelB"));
        labelB->setFont(font);
        labelB->setScaledContents(true);

        gridLayout_4->addWidget(labelB, 8, 0, 1, 1);

        lbBG54 = new QLabel(tabDRO);
        lbBG54->setObjectName(QStringLiteral("lbBG54"));
        lbBG54->setFrameShape(QFrame::Box);

        gridLayout_4->addWidget(lbBG54, 8, 1, 1, 1);

        lbBG53 = new QLabel(tabDRO);
        lbBG53->setObjectName(QStringLiteral("lbBG53"));
        lbBG53->setFrameShape(QFrame::Box);

        gridLayout_4->addWidget(lbBG53, 8, 2, 1, 1);

        lbBx = new QLabel(tabDRO);
        lbBx->setObjectName(QStringLiteral("lbBx"));
        lbBx->setFrameShape(QFrame::Box);

        gridLayout_4->addWidget(lbBx, 8, 3, 1, 1);

        labelC = new QLabel(tabDRO);
        labelC->setObjectName(QStringLiteral("labelC"));
        labelC->setFont(font);
        labelC->setScaledContents(true);

        gridLayout_4->addWidget(labelC, 9, 0, 1, 1);

        lbCG54 = new QLabel(tabDRO);
        lbCG54->setObjectName(QStringLiteral("lbCG54"));
        lbCG54->setFrameShape(QFrame::Box);

        gridLayout_4->addWidget(lbCG54, 9, 1, 1, 1);

        lbCG53 = new QLabel(tabDRO);
        lbCG53->setObjectName(QStringLiteral("lbCG53"));
        lbCG53->setFrameShape(QFrame::Box);

        gridLayout_4->addWidget(lbCG53, 9, 2, 1, 1);

        lbCx = new QLabel(tabDRO);
        lbCx->setObjectName(QStringLiteral("lbCx"));
        lbCx->setFrameShape(QFrame::Box);

        gridLayout_4->addWidget(lbCx, 9, 3, 1, 1);

        tabView->addTab(tabDRO, QString());
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        gridLayout = new QGridLayout(tab);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        te_Code = new CodeEditor(tab);
        te_Code->setObjectName(QStringLiteral("te_Code"));

        gridLayout->addWidget(te_Code, 0, 0, 1, 1);

        tabView->addTab(tab, QString());

        gridLayout_6->addWidget(tabView, 1, 0, 1, 1);

        QtAxis->setCentralWidget(centralwidget);
        menubar = new QMenuBar(QtAxis);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 606, 23));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuMachine = new QMenu(menubar);
        menuMachine->setObjectName(QStringLiteral("menuMachine"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        menuVeiw = new QMenu(menubar);
        menuVeiw->setObjectName(QStringLiteral("menuVeiw"));
        QtAxis->setMenuBar(menubar);
        statusbar = new QStatusBar(QtAxis);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        QtAxis->setStatusBar(statusbar);
        toolBar = new QToolBar(QtAxis);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        toolBar->setFloatable(true);
        QtAxis->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuMachine->menuAction());
        menubar->addAction(menuVeiw->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(action_Reload);
        menuFile->addSeparator();
        menuFile->addAction(actionSaveAs);
        menuFile->addSeparator();
        menuFile->addAction(actionRecentFiles);
        menuFile->addAction(actionLoadLast);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuMachine->addAction(actionToggleEstop);
        menuMachine->addAction(actionToggleMachineOn);
        menuMachine->addSeparator();
        menuMachine->addAction(actionHome);
        menuMachine->addSeparator();
        menuMachine->addAction(actionRun);
        menuMachine->addSeparator();
        menuMachine->addSeparator();
        menuMachine->addAction(actionStopOnError);
        menuHelp->addAction(actionAboutQtAxis);
        menuHelp->addAction(actionAboutQt);
        menuVeiw->addAction(actionGremlin);
        toolBar->addAction(actionToggleEstop);
        toolBar->addAction(actionToggleMachineOn);
        toolBar->addAction(actionHome);
        toolBar->addSeparator();
        toolBar->addAction(actionOpen);
        toolBar->addSeparator();
        toolBar->addAction(actionRunProgram);
        toolBar->addAction(actionPauseProgram);
        toolBar->addAction(actionStep);
        toolBar->addAction(actionStopProgram);
        toolBar->addSeparator();
        toolBar->addAction(actionAboutQtAxis);
        toolBar->addAction(actionAboutQt);

        retranslateUi(QtAxis);
        QObject::connect(slideJog, SIGNAL(valueChanged(int)), QtAxis, SLOT(onJogSliderChanged(int)));
        QObject::connect(tabControl, SIGNAL(currentChanged(int)), QtAxis, SLOT(onTabControlChanged(int)));
        QObject::connect(le_MDI, SIGNAL(returnPressed()), QtAxis, SLOT(onReturnMDICommand()));
        QObject::connect(pb_MDIClear, SIGNAL(clicked()), QtAxis, SLOT(onMdiClear()));
        QObject::connect(pb_MDICopy, SIGNAL(clicked()), QtAxis, SLOT(onMdiCopy()));
        QObject::connect(slideVelocity, SIGNAL(valueChanged(int)), QtAxis, SLOT(onVelocitySliderChanged(int)));
        QObject::connect(pbUnReHome, SIGNAL(clicked()), QtAxis, SLOT(onUnReHome()));
        QObject::connect(list_MDI, SIGNAL(itemEntered(QListWidgetItem*)), QtAxis, SLOT(onSelectFromMDIList(QListWidgetItem*)));
        QObject::connect(pbTouch, SIGNAL(clicked()), QtAxis, SLOT(onTouchOff()));
        QObject::connect(pb_MDI, SIGNAL(clicked()), QtAxis, SLOT(onReturnMDICommand()));
        QObject::connect(slideFeed, SIGNAL(valueChanged(int)), QtAxis, SLOT(onFeedSliderChanged(int)));
        QObject::connect(pb_MDIPaste, SIGNAL(clicked()), QtAxis, SLOT(onMdiPaste()));
        QObject::connect(list_MDI, SIGNAL(itemDoubleClicked(QListWidgetItem*)), QtAxis, SLOT(onSelectFromMDIList(QListWidgetItem*)));
        QObject::connect(pbHome, SIGNAL(clicked()), QtAxis, SLOT(onHome()));
        QObject::connect(rbA, SIGNAL(toggled(bool)), QtAxis, SLOT(onAxis(bool)));
        QObject::connect(rbX, SIGNAL(toggled(bool)), QtAxis, SLOT(onAxis(bool)));
        QObject::connect(rbV, SIGNAL(toggled(bool)), QtAxis, SLOT(onAxis(bool)));
        QObject::connect(rbB, SIGNAL(toggled(bool)), QtAxis, SLOT(onAxis(bool)));
        QObject::connect(rbZ, SIGNAL(toggled(bool)), QtAxis, SLOT(onAxis(bool)));
        QObject::connect(rbC, SIGNAL(toggled(bool)), QtAxis, SLOT(onAxis(bool)));
        QObject::connect(rbY, SIGNAL(toggled(bool)), QtAxis, SLOT(onAxis(bool)));
        QObject::connect(rbW, SIGNAL(toggled(bool)), QtAxis, SLOT(onAxis(bool)));
        QObject::connect(rbU, SIGNAL(toggled(bool)), QtAxis, SLOT(onAxis(bool)));
        QObject::connect(tabView, SIGNAL(currentChanged(int)), QtAxis, SLOT(onTabViewChanged(int)));

        tabControl->setCurrentIndex(0);
        tabView->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(QtAxis);
    } // setupUi

    void retranslateUi(QMainWindow *QtAxis)
    {
        QtAxis->setWindowTitle(QApplication::translate("QtAxis", "QtAxis", 0));
        actionExit->setText(QApplication::translate("QtAxis", "E&xit", 0));
        actionExit->setShortcut(QApplication::translate("QtAxis", "Ctrl+X", 0));
        actionOpen->setText(QApplication::translate("QtAxis", "Open", 0));
#ifndef QT_NO_TOOLTIP
        actionOpen->setToolTip(QApplication::translate("QtAxis", "Open (Ctrl+0)", 0));
#endif // QT_NO_TOOLTIP
        actionOpen->setShortcut(QApplication::translate("QtAxis", "Ctrl+O", 0));
        actionRecentFiles->setText(QApplication::translate("QtAxis", "Recent Files", 0));
        actionEdit->setText(QApplication::translate("QtAxis", "Edit", 0));
        actionReload->setText(QApplication::translate("QtAxis", "Reload", 0));
#ifndef QT_NO_TOOLTIP
        actionReload->setToolTip(QApplication::translate("QtAxis", "Reload (CTRL+R)", 0));
#endif // QT_NO_TOOLTIP
        actionReload->setShortcut(QApplication::translate("QtAxis", "Ctrl+R", 0));
        actionProperties->setText(QApplication::translate("QtAxis", "Properties", 0));
        actionSaveAs->setText(QApplication::translate("QtAxis", "Save As", 0));
#ifndef QT_NO_TOOLTIP
        actionSaveAs->setToolTip(QApplication::translate("QtAxis", "Save As (Ctrl + Shift + S)", 0));
#endif // QT_NO_TOOLTIP
        actionSaveAs->setShortcut(QApplication::translate("QtAxis", "Ctrl+Shift+S", 0));
        actionToolTable->setText(QApplication::translate("QtAxis", "Edit Tool Table", 0));
#ifndef QT_NO_TOOLTIP
        actionToolTable->setToolTip(QApplication::translate("QtAxis", "Edit Tool Table", 0));
#endif // QT_NO_TOOLTIP
        actionReloadToolTable->setText(QApplication::translate("QtAxis", "Reload Tool Table", 0));
        actionToggleEstop->setText(QApplication::translate("QtAxis", "Toggle &ESTOP", 0));
#ifndef QT_NO_TOOLTIP
        actionToggleEstop->setToolTip(QApplication::translate("QtAxis", "Toggle ESTOP (F1)", 0));
#endif // QT_NO_TOOLTIP
        actionToggleEstop->setShortcut(QApplication::translate("QtAxis", "F1", 0));
        actionToggleMachineOn->setText(QApplication::translate("QtAxis", "Toggle &Machine ON", 0));
#ifndef QT_NO_TOOLTIP
        actionToggleMachineOn->setToolTip(QApplication::translate("QtAxis", "Toggle Machine ON (F2)", 0));
#endif // QT_NO_TOOLTIP
        actionToggleMachineOn->setShortcut(QApplication::translate("QtAxis", "F2", 0));
        actionRunProgram->setText(QApplication::translate("QtAxis", "Run Program", 0));
#ifndef QT_NO_TOOLTIP
        actionRunProgram->setToolTip(QApplication::translate("QtAxis", "Run Program (R)", 0));
#endif // QT_NO_TOOLTIP
        actionRunProgram->setShortcut(QApplication::translate("QtAxis", "R", 0));
        actionPauseProgram->setText(QApplication::translate("QtAxis", "Pause Program", 0));
#ifndef QT_NO_TOOLTIP
        actionPauseProgram->setToolTip(QApplication::translate("QtAxis", "Pause Program (Space)", 0));
#endif // QT_NO_TOOLTIP
        actionPauseProgram->setShortcut(QApplication::translate("QtAxis", "Space", 0));
        actionStopProgram->setText(QApplication::translate("QtAxis", "Stop Program", 0));
#ifndef QT_NO_TOOLTIP
        actionStopProgram->setToolTip(QApplication::translate("QtAxis", "Stop Program (Esc)", 0));
#endif // QT_NO_TOOLTIP
        actionStopProgram->setShortcut(QApplication::translate("QtAxis", "Esc", 0));
        actionStep->setText(QApplication::translate("QtAxis", "Step", 0));
#ifndef QT_NO_TOOLTIP
        actionStep->setToolTip(QApplication::translate("QtAxis", "Step (S)", 0));
#endif // QT_NO_TOOLTIP
        actionStep->setShortcut(QApplication::translate("QtAxis", "S", 0));
        actionAboutQtAxis->setText(QApplication::translate("QtAxis", "&About QtAxis", 0));
        actionAboutQt->setText(QApplication::translate("QtAxis", "About &Qt", 0));
        actionHome->setText(QApplication::translate("QtAxis", "&Home", 0));
#ifndef QT_NO_TOOLTIP
        actionHome->setToolTip(QApplication::translate("QtAxis", "Home (Home)", 0));
#endif // QT_NO_TOOLTIP
        actionHome->setShortcut(QApplication::translate("QtAxis", "Home", 0));
        actionLoadLast->setText(QApplication::translate("QtAxis", "&Load Last File", 0));
        actionLoadLast->setShortcut(QApplication::translate("QtAxis", "Ctrl+L", 0));
        actionOptionalStop->setText(QApplication::translate("QtAxis", "Optional Stop", 0));
#ifndef QT_NO_TOOLTIP
        actionOptionalStop->setToolTip(QApplication::translate("QtAxis", "Optional Stop", 0));
#endif // QT_NO_TOOLTIP
        actionRun->setText(QApplication::translate("QtAxis", "&Run", 0));
        actionRun->setShortcut(QApplication::translate("QtAxis", "R", 0));
        actionGremlin->setText(QApplication::translate("QtAxis", "Gremlin_Settings", 0));
#ifndef QT_NO_TOOLTIP
        actionGremlin->setToolTip(QApplication::translate("QtAxis", "Launch Gremlin at start up", 0));
#endif // QT_NO_TOOLTIP
        actionGremlin->setShortcut(QApplication::translate("QtAxis", "Ctrl+G", 0));
        actionStopOnError->setText(QApplication::translate("QtAxis", "&Stop on Error", 0));
        actionStopOnError->setShortcut(QApplication::translate("QtAxis", "Esc", 0));
        action_Reload->setText(QApplication::translate("QtAxis", "&Reload", 0));
        action_Reload->setShortcut(QApplication::translate("QtAxis", "Ctrl+R", 0));
        rbX->setText(QApplication::translate("QtAxis", "X", 0));
        rbX->setShortcut(QApplication::translate("QtAxis", "X", 0));
        rbY->setText(QApplication::translate("QtAxis", "Y", 0));
        rbY->setShortcut(QApplication::translate("QtAxis", "Y", 0));
        rbZ->setText(QApplication::translate("QtAxis", "Z", 0));
        rbZ->setShortcut(QApplication::translate("QtAxis", "Z", 0));
        rbU->setText(QApplication::translate("QtAxis", "U", 0));
        rbU->setShortcut(QApplication::translate("QtAxis", "U", 0));
        rbV->setText(QApplication::translate("QtAxis", "V", 0));
        rbV->setShortcut(QApplication::translate("QtAxis", "V", 0));
        rbW->setText(QApplication::translate("QtAxis", "W", 0));
        rbW->setShortcut(QApplication::translate("QtAxis", "W", 0));
        rbA->setText(QApplication::translate("QtAxis", "A", 0));
        rbA->setShortcut(QApplication::translate("QtAxis", "A", 0));
        rbB->setText(QApplication::translate("QtAxis", "B", 0));
        rbB->setShortcut(QApplication::translate("QtAxis", "B", 0));
        rbC->setText(QApplication::translate("QtAxis", "C", 0));
        rbC->setShortcut(QApplication::translate("QtAxis", "C", 0));
        pbHome->setText(QApplication::translate("QtAxis", "Home", 0));
        pbHome->setShortcut(QApplication::translate("QtAxis", "Home", 0));
        pbUnReHome->setText(QString());
        pbUnReHome->setShortcut(QApplication::translate("QtAxis", "Ctrl+S", 0));
        pbTouch->setText(QApplication::translate("QtAxis", "Touch Off", 0));
        pbTouch->setShortcut(QApplication::translate("QtAxis", "Ctrl+T", 0));
        lbFeed->setText(QApplication::translate("QtAxis", "Feed Override:", 0));
        lbVelocity->setText(QApplication::translate("QtAxis", "Max Velocity", 0));
        pbJogYPlus->setText(QApplication::translate("QtAxis", "Y+", 0));
        pbJogXPlus->setText(QApplication::translate("QtAxis", "X+ >", 0));
        pbJogXMinus->setText(QApplication::translate("QtAxis", "< X-", 0));
        pbJogZPlus->setText(QApplication::translate("QtAxis", "Z+", 0));
        pbJogZMinus->setText(QApplication::translate("QtAxis", "Z-", 0));
        pbJogYMinus->setText(QApplication::translate("QtAxis", "Y-", 0));
        lbJog->setText(QApplication::translate("QtAxis", "Jog Speed:", 0));
        tabControl->setTabText(tabControl->indexOf(tabManual), QApplication::translate("QtAxis", "Manual", 0));
        pb_MDI->setText(QApplication::translate("QtAxis", "Go", 0));
        lb_activeGCodes->setText(QString());
        lb_activeMCodes->setText(QString());
        lb_feedSpeed->setText(QString());
        pb_MDIClear->setText(QApplication::translate("QtAxis", "Clear", 0));
        pb_MDICopy->setText(QApplication::translate("QtAxis", "Copy", 0));
        pb_MDIPaste->setText(QApplication::translate("QtAxis", "Paste to MDI", 0));
        tabControl->setTabText(tabControl->indexOf(tabMDI), QApplication::translate("QtAxis", "MDI", 0));
        pbClear->setText(QApplication::translate("QtAxis", "Clear", 0));
        tabView->setTabText(tabView->indexOf(tabPlot), QApplication::translate("QtAxis", "Messages", 0));
        lbHeaderG54->setText(QApplication::translate("QtAxis", "G54", 0));
        lbHeaderG53->setText(QApplication::translate("QtAxis", "G53", 0));
        lbHeaderx->setText(QString());
        labelX->setText(QApplication::translate("QtAxis", "X:", 0));
        lbXG54->setText(QString());
        lbXG53->setText(QString());
        lbXx->setText(QString());
        labelY->setText(QApplication::translate("QtAxis", "Y:", 0));
        lbYG54->setText(QString());
        lbYG53->setText(QString());
        lbYx->setText(QString());
        labelZ->setText(QApplication::translate("QtAxis", "Z:", 0));
        lbZG54->setText(QString());
        lbZG53->setText(QString());
        lbZx->setText(QString());
        labelU->setText(QApplication::translate("QtAxis", "U:", 0));
        lbUG54->setText(QString());
        lbUG53->setText(QString());
        lbUx->setText(QString());
        labelV->setText(QApplication::translate("QtAxis", "V:", 0));
        lbVG54->setText(QString());
        lbVG53->setText(QString());
        lbVx->setText(QString());
        labelW->setText(QApplication::translate("QtAxis", "W:", 0));
        lbWG54->setText(QString());
        lbWG53->setText(QString());
        lbWx->setText(QString());
        labelA->setText(QApplication::translate("QtAxis", "A:", 0));
        lbAG54->setText(QString());
        lbAG53->setText(QString());
        lbAx->setText(QString());
        labelB->setText(QApplication::translate("QtAxis", "B:", 0));
        lbBG54->setText(QString());
        lbBG53->setText(QString());
        lbBx->setText(QString());
        labelC->setText(QApplication::translate("QtAxis", "C:", 0));
        lbCG54->setText(QString());
        lbCG53->setText(QString());
        lbCx->setText(QString());
        tabView->setTabText(tabView->indexOf(tabDRO), QApplication::translate("QtAxis", "DRO", 0));
        tabView->setTabText(tabView->indexOf(tab), QApplication::translate("QtAxis", "G Code", 0));
        menuFile->setTitle(QApplication::translate("QtAxis", "&File", 0));
        menuMachine->setTitle(QApplication::translate("QtAxis", "&Machine", 0));
        menuHelp->setTitle(QApplication::translate("QtAxis", "&Help", 0));
        menuVeiw->setTitle(QApplication::translate("QtAxis", "&View", 0));
        toolBar->setWindowTitle(QApplication::translate("QtAxis", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class QtAxis: public Ui_QtAxis {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AXIS_H
