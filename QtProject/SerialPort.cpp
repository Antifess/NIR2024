#include "SerialPort.h"
#include "structs_tools.h"

#include <QMessageBox>

#define START_BYTE 0x55
#define STOP_BYTE 0xAA

SerialPort::SerialPort(QObject *parent)
    : QObject{parent},
    _serialPort(nullptr)
{

}

bool SerialPort::connect(QString portName)
{
    if (_serialPort != nullptr){
        _serialPort->close();
        delete _serialPort;
    }
    _serialPort = new QSerialPort();
    _serialPort->setPortName(portName);
    //_serialPort->setBaudRate(QSerialPort::Baud9600);
    _serialPort->setBaudRate(230400);
    _serialPort->setDataBits(QSerialPort::Data8);
    _serialPort->setParity(QSerialPort::NoParity);
    _serialPort->setStopBits(QSerialPort::OneStop);
    if (_serialPort->open(QIODevice::ReadWrite)){
         QObject::connect(_serialPort, &QSerialPort::readyRead, this, &SerialPort::dataReady);
    }
    //_serialPort->clear();
    return _serialPort->isOpen();
}

qint64 SerialPort::write(QByteArray data)
{
    try{
        if(_serialPort == nullptr || !_serialPort->isOpen())
            throw 1;
        return _serialPort->write(data);
    }
    catch(int error){
        if(error == 1){
            return -1;
        }
    }
    return -1;
}

/*class FromQSerialPort : protected QSerialPort {
public:
    using QSerialPort::read; // делаем protected метод read публичным

    static int get(QSerialPort& port, QByteArray& data, int n) {
        data = port.read(n);
        return data.size();
    }
};//*/



SerialPort::~SerialPort()
{
    if (_serialPort != nullptr){
        _serialPort->close();
        delete _serialPort;
    }
}

int current_pos = 0;
int first_start = 0;
int last_stop = 0;
float got_start = 0;
float got_stop = 0;
//QByteArray buffer;
void SerialPort::dataReady()
{
    /*if(_serialPort->isOpen()){
        static QByteArray buffer; // буфер для хранения неполных данных
        buffer += _serialPort->readAll();
        while(buffer.size() >= 18) {
            QMessageBox::information(nullptr, "123", QString::number(buffer[0]));
            emit dataReceived(buffer.mid(0, 18));
            buffer.remove(0, 18);
        }
    }//*/
    /* ВЕРСИЯ С БАГОМ */
    if(_serialPort->isOpen()){
        static QByteArray buffer;
        ///static QByteArray to_read;
        ///to_read +=_serialPort->readAll();
        ///buffer += to_read[0];
        ///to_read.removeFirst();
        buffer += _serialPort->readAll();
        while(current_pos < buffer.size()){
            //qDebug() << "Poses" << current_pos << buffer.length() << "got_start: " << got_start << "got_stop: " << got_stop;
            switch((uint8_t)buffer[current_pos]){
                case START_BYTE:{
                    got_start++;
                    if(got_start == 1)
                        first_start = current_pos;
                    break;
                }
                case STOP_BYTE:{
                    got_stop++;
                    if(got_stop == 2)
                        last_stop = current_pos;
                    break;
                }
                default:
                    break;
            }
            if(got_stop == 2 && got_start == 2){
                got_start = 0;
                got_stop = 0;
                //qDebug()<< "CRCs" << computeCrc8(buffer.mid(first_start + 2, last_stop - first_start - 4))<<static_cast<uint8_t>(buffer[last_stop - 2]) << Qt::endl;
                if(computeCrc8(buffer.mid(first_start + 2, last_stop - first_start - 4)) == static_cast<uint8_t>(buffer[last_stop - 2])){
                    emit dataReceived(buffer.mid(first_start + 2, last_stop - first_start - 4), buffer.length());
                    buffer = buffer.mid(first_start, buffer.length() - first_start);
                    current_pos -= first_start;
                }
                else{
                    //QMessageBox::information(nullptr, "compute", QString::number(computeCrc8(buffer.mid(first_start + 2, last_stop - first_start - 4))));
                    //QMessageBox::information(nullptr, "buffer", QString::number((uint8_t)buffer[last_stop - 2]));
                    buffer.clear();
                    got_start = 0;
                    got_stop = 0;
                    current_pos = -1;
                    first_start = 0;
                    last_stop = 0;
                }
            }
            if(got_start > 2 || got_stop > 2){
                buffer.clear();
                got_start = 0;
                got_stop = 0;
                current_pos = -1;
                first_start = 0;
                last_stop = 0;
            }
            current_pos++;
        }
        //}
    }
    /* Версия через вектор
    if(_serialPort->isOpen()){
        QByteArray to_read;
        static std::vector<uint8_t> buffer; // буфер для хранения неполных данных
        if(_serialPort->readBufferSize() > 0){
            to_read +=_serialPort->readAll();
            buffer.push_back((uint8_t)to_read[0]);
            to_read.removeFirst();
        }
        //buffer.push_back(_serialPort->readAll());
        while(current_pos < buffer.size()){
            switch((uint8_t)buffer[current_pos]){
            case START_BYTE:{
                got_start++;
                if(got_start == 1)
                    first_start = current_pos;
                break;
            }
            case STOP_BYTE:{
                got_stop++;
                if(got_stop == 2)
                    last_stop = current_pos;
                if(got_stop == 2 && got_start == 2){
                    got_start = 0;
                    got_stop = 0;
                    std::vector<uint8_t> found_cmd(&buffer[first_start + 2], &buffer[last_stop - first_start - 4]);
                    QByteArray* found_cmd_qbyte = new QByteArray(reinterpret_cast<const char*>(found_cmd.data()), found_cmd.size());
                    if(computeCrc8Vector(found_cmd) == buffer[last_stop - 2]){
                        emit dataReceived(found_cmd_qbyte->data(), buffer.size());
                         std::vector<uint8_t> upd(&buffer[first_start], &buffer[buffer.size() - first_start]);
                        buffer = upd;
                        current_pos -= first_start;

                    }
                    else{
                        //QMessageBox::information(nullptr, "", QString::number(computeCrc8(buffer.mid(first_start + 2, last_stop - first_start - 4))));
                        //QMessageBox::information(nullptr, "", QString::number((uint8_t)buffer[last_stop - 2]));
                    }
                }
                break;
            }
            default:
                break;

            }
            current_pos++;
        }
    }*/
}
