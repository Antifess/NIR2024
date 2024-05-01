/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *btnOpenPort;
    QListWidget *lstMessages;
    QListWidget *lstA1;
    QListWidget *lstA2;
    QListWidget *lstA3;
    QLabel *lblSend;
    QLabel *lblGot;
    QCustomPlot *customplot;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QPushButton *pushButtonAngles;
    QPushButton *pushButtonAngularSpeeds;
    QPushButton *pushButtonLinearAccelerations;
    QPushButton *pushButtonLinearSpeeds;
    QPushButton *pushButtonLinearCoordinates;
    QPushButton *pushButtonDEBUGRequest;
    QGroupBox *groupBoxRequest;
    QPushButton *btnStart;
    QPushButton *btnStop;
    QLineEdit *lineEditDelay;
    QCheckBox *checkBoxAngles;
    QCheckBox *checkBoxAngularSpeeds;
    QCheckBox *checkBoxLinearAccelerations;
    QCheckBox *checkBoxLinearSpeeds;
    QCheckBox *checkBoxLinearCoordinates;
    QPushButton *btnSendCloseRequest;
    QGroupBox *groupBoxSettings;
    QLineEdit *lineEditA1;
    QCheckBox *checkBoxAngles_cmd;
    QCheckBox *checkBoxAngularSpeeds_cmd;
    QCheckBox *checkBoxLinearAccelerations_cmd;
    QCheckBox *checkBoxLinearSpeeds_cmd;
    QCheckBox *checkBoxLinearCoordinates_cmd;
    QLineEdit *lineEditA2;
    QLineEdit *lineEditA3;
    QPushButton *btnSend;
    QPushButton *btnSendCloseCommand;
    QLabel *labelBufferL;
    QGroupBox *groupBoxCmdAdd;
    QLineEdit *lineEditName;
    QLineEdit *lineEditParamsN;
    QLineEdit *lineEditIdAlias;
    QLineEdit *lineEditIdNumber;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QPushButton *pushButtonAddCMD;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1200, 682);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        btnOpenPort = new QPushButton(centralwidget);
        btnOpenPort->setObjectName("btnOpenPort");
        btnOpenPort->setGeometry(QRect(10, 210, 71, 24));
        lstMessages = new QListWidget(centralwidget);
        lstMessages->setObjectName("lstMessages");
        lstMessages->setGeometry(QRect(330, 370, 81, 141));
        lstA1 = new QListWidget(centralwidget);
        lstA1->setObjectName("lstA1");
        lstA1->setGeometry(QRect(420, 370, 81, 141));
        lstA2 = new QListWidget(centralwidget);
        lstA2->setObjectName("lstA2");
        lstA2->setGeometry(QRect(510, 370, 81, 141));
        lstA3 = new QListWidget(centralwidget);
        lstA3->setObjectName("lstA3");
        lstA3->setGeometry(QRect(600, 370, 81, 141));
        lblSend = new QLabel(centralwidget);
        lblSend->setObjectName("lblSend");
        lblSend->setGeometry(QRect(630, 300, 49, 31));
        lblGot = new QLabel(centralwidget);
        lblGot->setObjectName("lblGot");
        lblGot->setGeometry(QRect(700, 300, 49, 31));
        customplot = new QCustomPlot(centralwidget);
        customplot->setObjectName("customplot");
        customplot->setGeometry(QRect(340, 10, 801, 351));
        scrollArea = new QScrollArea(centralwidget);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setGeometry(QRect(10, 10, 311, 191));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 309, 189));
        pushButtonAngles = new QPushButton(scrollAreaWidgetContents);
        pushButtonAngles->setObjectName("pushButtonAngles");
        pushButtonAngles->setGeometry(QRect(10, 10, 291, 24));
        pushButtonAngularSpeeds = new QPushButton(scrollAreaWidgetContents);
        pushButtonAngularSpeeds->setObjectName("pushButtonAngularSpeeds");
        pushButtonAngularSpeeds->setGeometry(QRect(10, 40, 291, 24));
        pushButtonLinearAccelerations = new QPushButton(scrollAreaWidgetContents);
        pushButtonLinearAccelerations->setObjectName("pushButtonLinearAccelerations");
        pushButtonLinearAccelerations->setGeometry(QRect(10, 70, 291, 24));
        pushButtonLinearSpeeds = new QPushButton(scrollAreaWidgetContents);
        pushButtonLinearSpeeds->setObjectName("pushButtonLinearSpeeds");
        pushButtonLinearSpeeds->setGeometry(QRect(10, 100, 291, 24));
        pushButtonLinearCoordinates = new QPushButton(scrollAreaWidgetContents);
        pushButtonLinearCoordinates->setObjectName("pushButtonLinearCoordinates");
        pushButtonLinearCoordinates->setGeometry(QRect(10, 130, 291, 24));
        pushButtonDEBUGRequest = new QPushButton(scrollAreaWidgetContents);
        pushButtonDEBUGRequest->setObjectName("pushButtonDEBUGRequest");
        pushButtonDEBUGRequest->setGeometry(QRect(10, 160, 291, 24));
        scrollArea->setWidget(scrollAreaWidgetContents);
        groupBoxRequest = new QGroupBox(centralwidget);
        groupBoxRequest->setObjectName("groupBoxRequest");
        groupBoxRequest->setGeometry(QRect(0, 350, 231, 231));
        btnStart = new QPushButton(groupBoxRequest);
        btnStart->setObjectName("btnStart");
        btnStart->setGeometry(QRect(10, 70, 61, 24));
        btnStop = new QPushButton(groupBoxRequest);
        btnStop->setObjectName("btnStop");
        btnStop->setGeometry(QRect(10, 100, 61, 24));
        lineEditDelay = new QLineEdit(groupBoxRequest);
        lineEditDelay->setObjectName("lineEditDelay");
        lineEditDelay->setGeometry(QRect(10, 30, 61, 24));
        checkBoxAngles = new QCheckBox(groupBoxRequest);
        checkBoxAngles->setObjectName("checkBoxAngles");
        checkBoxAngles->setGeometry(QRect(90, 30, 101, 22));
        checkBoxAngularSpeeds = new QCheckBox(groupBoxRequest);
        checkBoxAngularSpeeds->setObjectName("checkBoxAngularSpeeds");
        checkBoxAngularSpeeds->setGeometry(QRect(90, 60, 111, 22));
        checkBoxLinearAccelerations = new QCheckBox(groupBoxRequest);
        checkBoxLinearAccelerations->setObjectName("checkBoxLinearAccelerations");
        checkBoxLinearAccelerations->setGeometry(QRect(90, 90, 131, 22));
        checkBoxLinearSpeeds = new QCheckBox(groupBoxRequest);
        checkBoxLinearSpeeds->setObjectName("checkBoxLinearSpeeds");
        checkBoxLinearSpeeds->setGeometry(QRect(90, 120, 121, 22));
        checkBoxLinearCoordinates = new QCheckBox(groupBoxRequest);
        checkBoxLinearCoordinates->setObjectName("checkBoxLinearCoordinates");
        checkBoxLinearCoordinates->setGeometry(QRect(90, 150, 131, 22));
        btnSendCloseRequest = new QPushButton(groupBoxRequest);
        btnSendCloseRequest->setObjectName("btnSendCloseRequest");
        btnSendCloseRequest->setGeometry(QRect(10, 130, 61, 24));
        groupBoxSettings = new QGroupBox(centralwidget);
        groupBoxSettings->setObjectName("groupBoxSettings");
        groupBoxSettings->setGeometry(QRect(0, 350, 231, 231));
        lineEditA1 = new QLineEdit(groupBoxSettings);
        lineEditA1->setObjectName("lineEditA1");
        lineEditA1->setGeometry(QRect(10, 30, 61, 24));
        checkBoxAngles_cmd = new QCheckBox(groupBoxSettings);
        checkBoxAngles_cmd->setObjectName("checkBoxAngles_cmd");
        checkBoxAngles_cmd->setGeometry(QRect(90, 30, 101, 22));
        checkBoxAngularSpeeds_cmd = new QCheckBox(groupBoxSettings);
        checkBoxAngularSpeeds_cmd->setObjectName("checkBoxAngularSpeeds_cmd");
        checkBoxAngularSpeeds_cmd->setGeometry(QRect(90, 60, 111, 22));
        checkBoxLinearAccelerations_cmd = new QCheckBox(groupBoxSettings);
        checkBoxLinearAccelerations_cmd->setObjectName("checkBoxLinearAccelerations_cmd");
        checkBoxLinearAccelerations_cmd->setGeometry(QRect(90, 90, 131, 22));
        checkBoxLinearSpeeds_cmd = new QCheckBox(groupBoxSettings);
        checkBoxLinearSpeeds_cmd->setObjectName("checkBoxLinearSpeeds_cmd");
        checkBoxLinearSpeeds_cmd->setGeometry(QRect(90, 120, 121, 22));
        checkBoxLinearCoordinates_cmd = new QCheckBox(groupBoxSettings);
        checkBoxLinearCoordinates_cmd->setObjectName("checkBoxLinearCoordinates_cmd");
        checkBoxLinearCoordinates_cmd->setGeometry(QRect(90, 150, 131, 22));
        lineEditA2 = new QLineEdit(groupBoxSettings);
        lineEditA2->setObjectName("lineEditA2");
        lineEditA2->setGeometry(QRect(10, 60, 61, 24));
        lineEditA3 = new QLineEdit(groupBoxSettings);
        lineEditA3->setObjectName("lineEditA3");
        lineEditA3->setGeometry(QRect(10, 90, 61, 24));
        btnSend = new QPushButton(groupBoxSettings);
        btnSend->setObjectName("btnSend");
        btnSend->setGeometry(QRect(10, 120, 61, 24));
        btnSendCloseCommand = new QPushButton(groupBoxSettings);
        btnSendCloseCommand->setObjectName("btnSendCloseCommand");
        btnSendCloseCommand->setGeometry(QRect(10, 150, 61, 24));
        labelBufferL = new QLabel(centralwidget);
        labelBufferL->setObjectName("labelBufferL");
        labelBufferL->setGeometry(QRect(690, 370, 49, 16));
        groupBoxCmdAdd = new QGroupBox(centralwidget);
        groupBoxCmdAdd->setObjectName("groupBoxCmdAdd");
        groupBoxCmdAdd->setGeometry(QRect(889, 370, 251, 191));
        lineEditName = new QLineEdit(groupBoxCmdAdd);
        lineEditName->setObjectName("lineEditName");
        lineEditName->setGeometry(QRect(110, 30, 113, 24));
        lineEditParamsN = new QLineEdit(groupBoxCmdAdd);
        lineEditParamsN->setObjectName("lineEditParamsN");
        lineEditParamsN->setGeometry(QRect(110, 60, 113, 24));
        lineEditIdAlias = new QLineEdit(groupBoxCmdAdd);
        lineEditIdAlias->setObjectName("lineEditIdAlias");
        lineEditIdAlias->setGeometry(QRect(110, 90, 113, 24));
        lineEditIdNumber = new QLineEdit(groupBoxCmdAdd);
        lineEditIdNumber->setObjectName("lineEditIdNumber");
        lineEditIdNumber->setGeometry(QRect(110, 120, 113, 24));
        label = new QLabel(groupBoxCmdAdd);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 30, 71, 16));
        label_2 = new QLabel(groupBoxCmdAdd);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 60, 71, 16));
        label_3 = new QLabel(groupBoxCmdAdd);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 90, 71, 16));
        label_4 = new QLabel(groupBoxCmdAdd);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 120, 71, 16));
        pushButtonAddCMD = new QPushButton(groupBoxCmdAdd);
        pushButtonAddCMD->setObjectName("pushButtonAddCMD");
        pushButtonAddCMD->setGeometry(QRect(10, 150, 80, 24));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1200, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        btnOpenPort->setText(QCoreApplication::translate("MainWindow", "Open Port", nullptr));
        lblSend->setText(QString());
        lblGot->setText(QString());
        pushButtonAngles->setText(QCoreApplication::translate("MainWindow", "Angles", nullptr));
        pushButtonAngularSpeeds->setText(QCoreApplication::translate("MainWindow", "Angular Speeds", nullptr));
        pushButtonLinearAccelerations->setText(QCoreApplication::translate("MainWindow", "Linear Accelerations", nullptr));
        pushButtonLinearSpeeds->setText(QCoreApplication::translate("MainWindow", "Linear Speeds", nullptr));
        pushButtonLinearCoordinates->setText(QCoreApplication::translate("MainWindow", "Linear Coordinates", nullptr));
        pushButtonDEBUGRequest->setText(QCoreApplication::translate("MainWindow", "DEBUG Request", nullptr));
        groupBoxRequest->setTitle(QCoreApplication::translate("MainWindow", "                      Request Settings", nullptr));
        btnStart->setText(QCoreApplication::translate("MainWindow", "Start", nullptr));
        btnStop->setText(QCoreApplication::translate("MainWindow", "Stop", nullptr));
        checkBoxAngles->setText(QCoreApplication::translate("MainWindow", "Angles", nullptr));
        checkBoxAngularSpeeds->setText(QCoreApplication::translate("MainWindow", "Angular Speeds", nullptr));
        checkBoxLinearAccelerations->setText(QCoreApplication::translate("MainWindow", "Linear Accelerations", nullptr));
        checkBoxLinearSpeeds->setText(QCoreApplication::translate("MainWindow", "Linear Speeds", nullptr));
        checkBoxLinearCoordinates->setText(QCoreApplication::translate("MainWindow", "Linear Coordinates", nullptr));
        btnSendCloseRequest->setText(QCoreApplication::translate("MainWindow", "Close", nullptr));
        groupBoxSettings->setTitle(QCoreApplication::translate("MainWindow", "                      Command Settings", nullptr));
        checkBoxAngles_cmd->setText(QCoreApplication::translate("MainWindow", "Angles", nullptr));
        checkBoxAngularSpeeds_cmd->setText(QCoreApplication::translate("MainWindow", "Angular Speeds", nullptr));
        checkBoxLinearAccelerations_cmd->setText(QCoreApplication::translate("MainWindow", "Linear Accelerations", nullptr));
        checkBoxLinearSpeeds_cmd->setText(QCoreApplication::translate("MainWindow", "Linear Speeds", nullptr));
        checkBoxLinearCoordinates_cmd->setText(QCoreApplication::translate("MainWindow", "Linear Coordinates", nullptr));
        btnSend->setText(QCoreApplication::translate("MainWindow", "Send", nullptr));
        btnSendCloseCommand->setText(QCoreApplication::translate("MainWindow", "Close", nullptr));
        labelBufferL->setText(QString());
        groupBoxCmdAdd->setTitle(QCoreApplication::translate("MainWindow", "New cmd params", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Class Name", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Parameters n", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "ID Alias", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "ID number", nullptr));
        pushButtonAddCMD->setText(QCoreApplication::translate("MainWindow", "Add", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
