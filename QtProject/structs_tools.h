#ifndef STRUCTS_TOOLS_H
#define STRUCTS_TOOLS_H
#include <QByteArray>

/*
1) команда 3 угла
2) команда 3 угловых скорости
3) команда 3 линейных ускорения
4) команда 3 линейных скорости
5) команда 3 линейных координаты
*/

/*namespace cmd_ids{
    enum id : uint8_t{
        null = 0x00,
        start = 0x01,
        stop = 0x02,
        angles = 0x03,
        ang_speeds = 0x04,
        lin_accelerations = 0x05,
        lin_speeds = 0x06,
        lin_coords = 0x07,
    };
}*/

QByteArray prepare_to_send(QByteArray cmd);

/**
 * @brief Вычисление байта четности
 */

quint8 computeCrc8(const QByteArray& data);

quint8 computeCrc8Vector(const std::vector<uint8_t>& data);

/*class __attribute__((packed)) Angles{
public:
    const cmd_ids::id id = cmd_ids::id::angles;

    float a1, a2, a3;

    Angles();
    Angles(float a1, float a2, float a3);
};

class __attribute__((packed)) AngularSpeeds{
public:
    const cmd_ids::id id = cmd_ids::id::ang_speeds;

    float a1, a2, a3;

    AngularSpeeds();
    AngularSpeeds(float a1, float a2, float a3);
};

class __attribute__((packed)) LinearAccelerations{
public:
    const cmd_ids::id id = cmd_ids::id::lin_accelerations;

    float a1, a2, a3;

    LinearAccelerations();
    LinearAccelerations(float a1, float a2, float a3);
};

class __attribute__((packed)) LinearSpeeds{
public:
    const cmd_ids::id id = cmd_ids::id::lin_speeds;

    float a1, a2, a3;

    LinearSpeeds();
    LinearSpeeds(float a1, float a2, float a3);
};

class __attribute__((packed)) LinearCoordinates{
public:
    const cmd_ids::id id = cmd_ids::id::lin_coords;

    float a1, a2, a3;

    LinearCoordinates();
    LinearCoordinates(float a1, float a2, float a3);
};

class __attribute__((packed)) Request{
public:

    cmd_ids::id id;
    int delay;


    uint8_t reserved:3;
    uint8_t is_angles:1;
    uint8_t is_ang_speeds:1;
    uint8_t is_lin_accelerations:1;
    uint8_t is_lin_speeds:1;
    uint8_t is_lin_coords:1;


    Request(cmd_ids::id id, int delay, bool is_angles, bool is_ang_speeds, bool is_lin_accelerations, bool is_lin_speeds, bool is_lin_coords);
};*/





#endif // STRUCTS_TOOLS_H
