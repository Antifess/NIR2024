#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "structs_tools.h"
//#include "structs_cmds.h"
//#include <F:/ST/Proj/quadrocopter_stm32f4/App/Inc/structs_cmds.h>
#include "structs_cmds_common.h"
#include "qcustomplot.h"
#include "glwidget.h"
#include "commandextender.h"

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>


QVector<double> t = {0}, values = {0}, values1 = {0}, values2 = {0};
double DEBUG_DELAY;
int to_add_id = -1;
cmd_ids::id current_shown_data_type = cmd_ids::id::angles;

CommandExtender cmd_extender;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&_port, &SerialPort::dataReceived, this, &MainWindow::readData);
    ui->customplot->addGraph();
    ui->customplot->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->customplot->graph()->setLineStyle(QCPGraph::lsLine);
    ui->customplot->xAxis->setLabel("Time");
    ui->customplot->yAxis->setLabel("Angles");
    ui->customplot->xAxis->setRange(0, 1000);
    ui->customplot->yAxis->setRange(-360, 360);
    ui->customplot->addGraph();
    ui->customplot->graph(1)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->customplot->addGraph();
    ui->customplot->graph(2)->setScatterStyle(QCPScatterStyle::ssCircle);

    ui->customplot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    ui->customplot->graph(0)->setPen(QPen(QColor(255, 0, 0)));
    ui->customplot->graph(1)->setPen(QPen(QColor(0, 255, 0)));
    ui->customplot->graph(2)->setPen(QPen(QColor(0, 0, 255)));

    ui->groupBoxRequest->setVisible(false);
    ui->groupBoxSettings->setVisible(false);

    glWidget.show();

}

template<typename T>
void MainWindow::add_to_plot(T* cmd_ptr){
    bool was_deleted = false;
    values.append((double)cmd_ptr->a1);
    if(values.length() > 100){
        values.remove(0);
        was_deleted = true;
    }
    values1.append((double)cmd_ptr->a2);
    if(values1.length() > 100){
        values1.remove(0);
        was_deleted = true;
    }
    values2.append((double)cmd_ptr->a3);
    if(values2.length() > 100){
        values2.remove(0);
        was_deleted = true;
    }
    t.append(t.last() + 100);//DEBUG_DELAY);
    if(was_deleted){
        t.remove(0);
    }
    ui->customplot->graph(0)->setData(t, values);
    ui->customplot->graph(1)->setData(t, values1);
    ui->customplot->graph(2)->setData(t,  values2);
    ui->customplot->xAxis->rescale();
    ui->customplot->replot();
    ui->customplot->update();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnOpenPort_clicked()
{
    auto is_connected = _port.connect("COM5");
    if(!is_connected){
        QMessageBox::critical(this, "Error", "Error while connecting to port!");
    }
    else{
        QMessageBox::information(this, "Success", "Successfully conected to port!");
    }
}

void MainWindow::on_btnSend_clicked()
{

    float a1 = ui->lineEditA1->text().toFloat();
    float a2 = ui->lineEditA2->text().toFloat();
    float a3 = ui->lineEditA3->text().toFloat();

    switch(to_add_id){
        case 1:{
            auto c = AnglesCmd(a1, a2, a3);
            uint8_t* byteArray = reinterpret_cast<uint8_t*>(&c);
            this->cmds_list.append(prepare_to_send(QByteArray(reinterpret_cast<const char*>(byteArray), sizeof(AnglesCmd))));
            break;
        }
        case 2:{
            auto c = AngularSpeedsCmd(a1, a2, a3);
            uint8_t* byteArray = reinterpret_cast<uint8_t*>(&c);
            this->cmds_list.append(prepare_to_send(QByteArray(reinterpret_cast<const char*>(byteArray), sizeof(AngularSpeedsCmd))));
            break;
        }
        case 3:{
            auto c = LinearAccelerationsCmd(a1, a2, a3);
            uint8_t* byteArray = reinterpret_cast<uint8_t*>(&c);
            this->cmds_list.append(prepare_to_send(QByteArray(reinterpret_cast<const char*>(byteArray), sizeof(LinearAccelerationsCmd))));
            break;
        }
        case 4:{
            auto c = LinearSpeedsCmd(a1, a2, a3);
            uint8_t* byteArray = reinterpret_cast<uint8_t*>(&c);
            this->cmds_list.append(prepare_to_send(QByteArray(reinterpret_cast<const char*>(byteArray), sizeof(LinearSpeedsCmd))));
            break;
        }
        case 5:{
            auto c = LinearCoordinatesCmd(a1, a2, a3);
            uint8_t* byteArray = reinterpret_cast<uint8_t*>(&c);
            this->cmds_list.append(prepare_to_send(QByteArray(reinterpret_cast<const char*>(byteArray), sizeof(LinearCoordinatesCmd))));
            break;
        }
    }
    for(int i = 0; i< this->cmds_list.size(); i++){
        auto num_bytes = _port.write(this->cmds_list[i]);
        ui->lblSend->setText("Sent:\n" + QString::number(num_bytes) + " bytes");
        if(num_bytes == -1){
            QMessageBox::critical(this, "Error", "Error while writing to port!");
        }
    }
    this->cmds_list.clear();
}

void MainWindow::setlbl(int value){
    ui->labelBufferL->setText(QString::number(value));
}

void MainWindow::readData(QByteArray data, int l)
{
    ui->lblGot->setText("Got:\n" + QString::number(data.size()) + " bytes");
    ui->labelBufferL->setText(QString::number(l));
    if(data[0] == cmd_ids::angles){
        auto got_cmd = reinterpret_cast<AnglesCmd*>(data.data());
        //ui->lstMessages->addItem(QString::number((quint8)got_cmd->id));
       // ui->lstA1->addItem(QString::number(got_cmd->a1));
        //ui->lstA2->addItem(QString::number(got_cmd->a2));
        //ui->lstA3->addItem(QString::number(got_cmd->a3));

        glWidget.dataEvent(got_cmd->a1, got_cmd->a2, got_cmd->a3);


        if(got_cmd->id == current_shown_data_type)
            add_to_plot(got_cmd);
        /*bool was_deleted = false;
        values.append((double)got_cmd->a1);
        if(values.length() > 100){
            values.remove(0);
            was_deleted = true;
        }
        values1.append((double)got_cmd->a2);
        if(values1.length() > 100){
            values1.remove(0);
            was_deleted = true;
        }
        values2.append((double)got_cmd->a3);
        if(values2.length() > 100){
            values2.remove(0);
            was_deleted = true;
        }
        t.append(t.last() + 100);//DEBUG_DELAY);
        if(was_deleted){
            t.remove(0);
        }
        ui->customplot->graph(0)->setData(t, values);
        ui->customplot->graph(1)->setData(t, values1);
        ui->customplot->graph(2)->setData(t,  values2);
        ui->customplot->xAxis->rescale();
        ui->customplot->replot();
        ui->customplot->update();*/

    }
    if(data[0] == cmd_ids::ang_speeds){
        auto got_cmd = reinterpret_cast<AngularSpeedsCmd*>(data.data());
        //ui->lstMessages->addItem(QString::number((quint8)got_cmd->id));
        //ui->lstA1->addItem(QString::number(got_cmd->a1));
        //ui->lstA2->addItem(QString::number(got_cmd->a2));
        //ui->lstA3->addItem(QString::number(got_cmd->a3));
        if(got_cmd->id == current_shown_data_type)
            add_to_plot(got_cmd);
    }
    if(data[0] == cmd_ids::lin_accelerations){
        auto got_cmd = reinterpret_cast<LinearAccelerationsCmd*>(data.data());
        //ui->lstMessages->addItem(QString::number((quint8)got_cmd->id));
        //ui->lstA1->addItem(QString::number(got_cmd->a1));
        //ui->lstA2->addItem(QString::number(got_cmd->a2));
        //ui->lstA3->addItem(QString::number(got_cmd->a3));
        if(got_cmd->id == current_shown_data_type)
            add_to_plot(got_cmd);
    }
    if(data[0] == cmd_ids::lin_speeds){
        auto got_cmd = reinterpret_cast<LinearSpeedsCmd*>(data.data());
        //ui->lstMessages->addItem(QString::number((quint8)got_cmd->id));
        //ui->lstA1->addItem(QString::number(got_cmd->a1));
        //ui->lstA2->addItem(QString::number(got_cmd->a2));
        //ui->lstA3->addItem(QString::number(got_cmd->a3));
        if(got_cmd->id == current_shown_data_type)
            add_to_plot(got_cmd);
    }
    if(data[0] == cmd_ids::lin_coords){
        auto got_cmd = reinterpret_cast<LinearCoordinatesCmd*>(data.data());
        //ui->lstMessages->addItem(QString::number((quint8)got_cmd->id));
        //ui->lstA1->addItem(QString::number(got_cmd->a1));
        //ui->lstA2->addItem(QString::number(got_cmd->a2));
        //ui->lstA3->addItem(QString::number(got_cmd->a3));
        if(got_cmd->id == current_shown_data_type)
            add_to_plot(got_cmd);
    }
    if(data[0] == cmd_ids::start || data[0] == cmd_ids::stop){
        auto got_cmd = reinterpret_cast<Request*>(data.data());
        ui->lstMessages->addItem(QString::number((quint8)got_cmd->id));
        ui->lstA1->addItem(QString::number(got_cmd->delay));
        ui->lstA2->addItem(QString("-"));
        ui->lstA3->addItem(QString("-"));
        if(got_cmd->id == cmd_ids::start)
            DEBUG_DELAY = got_cmd->delay;
    }

}


void MainWindow::on_btnStart_clicked()
{
    int delay = ui->lineEditDelay->text().toInt();
    bool is_angles = ui->checkBoxAngles->isChecked();
    bool is_ang_speeds = ui->checkBoxAngularSpeeds->isChecked();
    bool is_lin_accelerations = ui->checkBoxLinearAccelerations->isChecked();
    bool is_lin_speeds = ui->checkBoxLinearSpeeds->isChecked();
    bool is_lin_coords = ui->checkBoxLinearCoordinates->isChecked();
    auto c = Request(cmd_ids::start, delay, is_angles, is_ang_speeds, is_lin_accelerations, is_lin_speeds, is_lin_coords);
    uint8_t* byteArray = reinterpret_cast<uint8_t*>(&c);
    this->cmds_list.append(prepare_to_send(QByteArray(reinterpret_cast<const char*>(byteArray), sizeof(Request))));
    for(int i = 0; i< this->cmds_list.size(); i++){
        auto num_bytes = _port.write(this->cmds_list[i]);
        ui->lblSend->setText("Sent:\n" + QString::number(num_bytes) + " bytes");
        if(num_bytes == -1){
            QMessageBox::critical(this, "Error", "Error while writing to port!");
        }
    }
    this->cmds_list.clear();
}


void MainWindow::on_btnStop_clicked()
{
    int delay = ui->lineEditDelay->text().toInt();
    bool is_angles = ui->checkBoxAngles->isChecked();
    bool is_ang_speeds = ui->checkBoxAngularSpeeds->isChecked();
    bool is_lin_accelerations = ui->checkBoxLinearAccelerations->isChecked();
    bool is_lin_speeds = ui->checkBoxLinearSpeeds->isChecked();
    bool is_lin_coords = ui->checkBoxLinearCoordinates->isChecked();
    auto c = Request(cmd_ids::stop, delay, is_angles, is_ang_speeds, is_lin_accelerations, is_lin_speeds, is_lin_coords);
    uint8_t* byteArray = reinterpret_cast<uint8_t*>(&c);
    this->cmds_list.append(prepare_to_send(QByteArray(reinterpret_cast<const char*>(byteArray), sizeof(Request))));
    for(int i = 0; i< this->cmds_list.size(); i++){
        auto num_bytes = _port.write(this->cmds_list[i]);
        ui->lblSend->setText("Sent:\n" + QString::number(num_bytes) + " bytes");
        if(num_bytes == -1){
            QMessageBox::critical(this, "Error", "Error while writing to port!");
        }
    }
    this->cmds_list.clear();
}


void MainWindow::on_pushButtonDEBUGRequest_clicked()
{
    ui->groupBoxRequest->setVisible(true);
    ui->groupBoxSettings->setVisible(false);
}


void MainWindow::on_pushButtonAngles_clicked()
{
    ui->groupBoxSettings->setVisible(true);
    ui->groupBoxRequest->setVisible(false);
    ui->checkBoxAngles_cmd->setCheckState(Qt::Checked);
    ui->checkBoxAngularSpeeds_cmd->setCheckState(Qt::Unchecked);
    ui->checkBoxLinearAccelerations_cmd->setCheckState(Qt::Unchecked);
    ui->checkBoxLinearSpeeds_cmd->setCheckState(Qt::Unchecked);
    ui->checkBoxLinearCoordinates_cmd->setCheckState(Qt::Unchecked);

    ui->checkBoxAngles_cmd->setEnabled(false);
    ui->checkBoxAngularSpeeds_cmd->setEnabled(false);
    ui->checkBoxLinearAccelerations_cmd->setEnabled(false);
    ui->checkBoxLinearSpeeds_cmd->setEnabled(false);
    ui->checkBoxLinearCoordinates_cmd->setEnabled(false);
    to_add_id = 1;


    values1 = {0};
    values2 = {0};
    values = {0};
    t = {0};
    ui->customplot->yAxis->setLabel("Angles");
    ui->customplot->update();
    current_shown_data_type = cmd_ids::id::angles;

}


void MainWindow::on_pushButtonAngularSpeeds_clicked()
{
    ui->groupBoxSettings->setVisible(true);
    ui->groupBoxRequest->setVisible(false);
    ui->checkBoxAngles_cmd->setCheckState(Qt::Unchecked);
    ui->checkBoxAngularSpeeds_cmd->setCheckState(Qt::Checked);
    ui->checkBoxLinearAccelerations_cmd->setCheckState(Qt::Unchecked);
    ui->checkBoxLinearSpeeds_cmd->setCheckState(Qt::Unchecked);
    ui->checkBoxLinearCoordinates_cmd->setCheckState(Qt::Unchecked);

    ui->checkBoxAngles_cmd->setEnabled(false);
    ui->checkBoxAngularSpeeds_cmd->setEnabled(false);
    ui->checkBoxLinearAccelerations_cmd->setEnabled(false);
    ui->checkBoxLinearSpeeds_cmd->setEnabled(false);
    ui->checkBoxLinearCoordinates_cmd->setEnabled(false);
    to_add_id = 2;

    values1 = {0};
    values2 = {0};
    values = {0};
    t = {0};
    ui->customplot->yAxis->setLabel("Anglar Speeds");
    ui->customplot->update();

    current_shown_data_type = cmd_ids::id::ang_speeds;
}


void MainWindow::on_pushButtonLinearAccelerations_clicked()
{
    ui->groupBoxSettings->setVisible(true);
    ui->groupBoxRequest->setVisible(false);
    ui->checkBoxAngles_cmd->setCheckState(Qt::Unchecked);
    ui->checkBoxAngularSpeeds_cmd->setCheckState(Qt::Unchecked);
    ui->checkBoxLinearAccelerations_cmd->setCheckState(Qt::Checked);
    ui->checkBoxLinearSpeeds_cmd->setCheckState(Qt::Unchecked);
    ui->checkBoxLinearCoordinates_cmd->setCheckState(Qt::Unchecked);

    ui->checkBoxAngles_cmd->setEnabled(false);
    ui->checkBoxAngularSpeeds_cmd->setEnabled(false);
    ui->checkBoxLinearAccelerations_cmd->setEnabled(false);
    ui->checkBoxLinearSpeeds_cmd->setEnabled(false);
    ui->checkBoxLinearCoordinates_cmd->setEnabled(false);
    to_add_id = 3;

    values1 = {0};
    values2 = {0};
    values = {0};
    t = {0};
    ui->customplot->yAxis->setLabel("Linear Accelerations");
    ui->customplot->update();
    current_shown_data_type = cmd_ids::id::lin_accelerations;
}


void MainWindow::on_pushButtonLinearSpeeds_clicked()
{
    ui->groupBoxSettings->setVisible(true);
    ui->groupBoxRequest->setVisible(false);
    ui->checkBoxAngles_cmd->setCheckState(Qt::Unchecked);
    ui->checkBoxAngularSpeeds_cmd->setCheckState(Qt::Unchecked);
    ui->checkBoxLinearAccelerations_cmd->setCheckState(Qt::Unchecked);
    ui->checkBoxLinearSpeeds_cmd->setCheckState(Qt::Checked);
    ui->checkBoxLinearCoordinates_cmd->setCheckState(Qt::Unchecked);

    ui->checkBoxAngles_cmd->setEnabled(false);
    ui->checkBoxAngularSpeeds_cmd->setEnabled(false);
    ui->checkBoxLinearAccelerations_cmd->setEnabled(false);
    ui->checkBoxLinearSpeeds_cmd->setEnabled(false);
    ui->checkBoxLinearCoordinates_cmd->setEnabled(false);
    to_add_id = 4;

    values1 = {0};
    values2 = {0};
    values = {0};
    t = {0};
    ui->customplot->yAxis->setLabel("Linear Speeds");
    ui->customplot->update();
    current_shown_data_type = cmd_ids::id::lin_speeds;
}


void MainWindow::on_pushButtonLinearCoordinates_clicked()
{
    ui->groupBoxSettings->setVisible(true);
    ui->groupBoxRequest->setVisible(false);
    ui->checkBoxAngles_cmd->setCheckState(Qt::Unchecked);
    ui->checkBoxAngularSpeeds_cmd->setCheckState(Qt::Unchecked);
    ui->checkBoxLinearAccelerations_cmd->setCheckState(Qt::Unchecked);
    ui->checkBoxLinearSpeeds_cmd->setCheckState(Qt::Unchecked);
    ui->checkBoxLinearCoordinates_cmd->setCheckState(Qt::Checked);

    ui->checkBoxAngles_cmd->setEnabled(false);
    ui->checkBoxAngularSpeeds_cmd->setEnabled(false);
    ui->checkBoxLinearAccelerations_cmd->setEnabled(false);
    ui->checkBoxLinearSpeeds_cmd->setEnabled(false);
    ui->checkBoxLinearCoordinates_cmd->setEnabled(false);
    to_add_id = 5;

    values1 = {0};
    values2 = {0};
    values = {0};
    t = {0};
    ui->customplot->yAxis->setLabel("Linear Coordinates");
    ui->customplot->update();
    current_shown_data_type = cmd_ids::id::lin_coords;
}


void MainWindow::on_btnSendCloseRequest_clicked()
{
    ui->groupBoxRequest->setVisible(false);
}


void MainWindow::on_btnSendCloseCommand_clicked()
{
    ui->groupBoxSettings->setVisible(false);
}


void MainWindow::on_pushButtonAddCMD_clicked()
{
    cmd_extender.add_cmd(ui->lineEditName->text().toStdString(), ui->lineEditIdAlias->text().toStdString(), ui->lineEditIdNumber->text().toInt(), ui->lineEditParamsN->text().toInt());
}

