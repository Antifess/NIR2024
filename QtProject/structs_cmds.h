//#ifndef STRUCTS_CMDS_H
//#define STRUCTS_CMDS_H
#include <cstdint>

namespace cmd_ids{
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
}

class __attribute__((packed)) AnglesCmd{
public:
    const cmd_ids::id id = cmd_ids::id::angles;

    float a1, a2, a3;

    AnglesCmd();
    AnglesCmd(float a1, float a2, float a3);
};

class __attribute__((packed)) AngularSpeedsCmd{
public:
    const cmd_ids::id id = cmd_ids::id::ang_speeds;

    float a1, a2, a3;

    AngularSpeedsCmd();
    AngularSpeedsCmd(float a1, float a2, float a3);
};

class __attribute__((packed)) LinearAccelerationsCmd{
public:
    const cmd_ids::id id = cmd_ids::id::lin_accelerations;

    float a1, a2, a3;

    LinearAccelerationsCmd();
    LinearAccelerationsCmd(float a1, float a2, float a3);
};

class __attribute__((packed)) LinearSpeedsCmd{
public:
    const cmd_ids::id id = cmd_ids::id::lin_speeds;

    float a1, a2, a3;

    LinearSpeedsCmd();
    LinearSpeedsCmd(float a1, float a2, float a3);
};

class __attribute__((packed)) LinearCoordinatesCmd{
public:
    const cmd_ids::id id = cmd_ids::id::lin_coords;

    float a1, a2, a3;

    LinearCoordinatesCmd();
    LinearCoordinatesCmd(float a1, float a2, float a3);
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
};

//#endif // STRUCTS_CMDS_H
