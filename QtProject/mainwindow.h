#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QtSerialPort/QSerialPort>
#include <QMessageBox>
#include "SerialPort.h"
#include <glwidget.h>

#include <QGraphicsScene>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QList<QByteArray> cmds_list;

    template<typename T>
    void add_to_plot(T* cmd_ptr);

private slots:
    void on_btnOpenPort_clicked();

    void on_btnSend_clicked();

    void readData(QByteArray data, int l);

    void on_btnStart_clicked();

    void on_btnStop_clicked();

    void on_pushButtonDEBUGRequest_clicked();

    void on_pushButtonAngles_clicked();

    void on_pushButtonAngularSpeeds_clicked();

    void on_pushButtonLinearAccelerations_clicked();

    void on_pushButtonLinearSpeeds_clicked();

    void on_pushButtonLinearCoordinates_clicked();

    void on_btnSendCloseRequest_clicked();

    void on_btnSendCloseCommand_clicked();

    void setlbl(int value);

    void on_pushButtonAddCMD_clicked();

private:
    Ui::MainWindow *ui;
    SerialPort _port;

    GLWidget glWidget;

    QGraphicsScene *scene;
};
#endif // MAINWINDOW_H
