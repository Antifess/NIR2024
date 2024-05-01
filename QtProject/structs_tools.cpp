#include "structs_tools.h"
#include <QtEndian>

quint8 computeCrc8(const QByteArray& data)
{
    const quint8 polynomial = 0x31; // Многочлен CRC-8
    quint8 crc = 0;

    foreach (char byte, data) {
        crc ^= byte; // Применяем операцию XOR между текущим значением CRC и текущим байтом данных

        for (int i = 0; i < 8; i++) {
            crc = (crc & 0x80) ? ((crc << 1) ^ polynomial) : (crc << 1); // Выполняем сдвиг CRC влево на 1 бит и, если старший бит равен 1, выполняем операцию XOR с многочленом
        }
    }

    return crc;
}

quint8 computeCrc8Vector(const std::vector<uint8_t>& data)
{
    const quint8 polynomial = 0x31; // Многочлен CRC-8
    quint8 crc = 0;

    foreach (char byte, data) {
        crc ^= byte; // Применяем операцию XOR между текущим значением CRC и текущим байтом данных

        for (int i = 0; i < 8; i++) {
            crc = (crc & 0x80) ? ((crc << 1) ^ polynomial) : (crc << 1); // Выполняем сдвиг CRC влево на 1 бит и, если старший бит равен 1, выполняем операцию XOR с многочленом
        }
    }

    return crc;
}


QByteArray prepare_to_send(QByteArray cmd){
    QByteArray result;
    result.append(0x55);
    result.append(0x55);
    result.append(cmd);

    //crc8
    result.append(computeCrc8(cmd));

    result.append(0x99);
    result.append(0x99);

    return result;
}

/*Angles::Angles()
{
    a1 = 0;
    a2 = 0;
    a3 = 0;
}

Angles::Angles(float a1, float a2, float a3)
{
    this->a1 = a1;
    this->a2 = a2;
    this->a3 = a3;
}

AngularSpeeds::AngularSpeeds()
{
    a1 = 0;
    a2 = 0;
    a3 = 0;
}

AngularSpeeds::AngularSpeeds(float a1, float a2, float a3)
{
    this->a1 = a1;
    this->a2 = a2;
    this->a3 = a3;
}

LinearAccelerations::LinearAccelerations()
{
    a1 = 0;
    a2 = 0;
    a3 = 0;
}

LinearAccelerations::LinearAccelerations(float a1, float a2, float a3)
{
    this->a1 = a1;
    this->a2 = a2;
    this->a3 = a3;
}

LinearSpeeds::LinearSpeeds()
{
    a1 = 0;
    a2 = 0;
    a3 = 0;
}

LinearSpeeds::LinearSpeeds(float a1, float a2, float a3)
{
    this->a1 = a1;
    this->a2 = a2;
    this->a3 = a3;
}

LinearCoordinates::LinearCoordinates()
{
    a1 = 0;
    a2 = 0;
    a3 = 0;
}

LinearCoordinates::LinearCoordinates(float a1, float a2, float a3)
{
    this->a1 = a1;
    this->a2 = a2;
    this->a3 = a3;
}

Request::Request(cmd_ids::id id,int delay, bool is_angles, bool is_ang_speeds, bool is_lin_accelerations, bool is_lin_speeds, bool is_lin_coords)
{
    this->id = id;
    this->delay = delay;
    reserved = 0;
    this->is_angles = is_angles;
    this->is_ang_speeds = is_ang_speeds;
    this->is_lin_accelerations = is_lin_accelerations;
    this->is_lin_speeds = is_lin_speeds;
    this->is_lin_coords = is_lin_coords;
}*/
