#include "structs_cmds_common.h"

AnglesCmd::AnglesCmd()
{
    a1 = 0;
    a2 = 0;
    a3 = 0;
}

AnglesCmd::AnglesCmd(float a1, float a2, float a3)
{
    this->a1 = a1;
    this->a2 = a2;
    this->a3 = a3;
}

AngularSpeedsCmd::AngularSpeedsCmd()
{
    a1 = 0;
    a2 = 0;
    a3 = 0;
}

AngularSpeedsCmd::AngularSpeedsCmd(float a1, float a2, float a3)
{
    this->a1 = a1;
    this->a2 = a2;
    this->a3 = a3;
}

LinearAccelerationsCmd::LinearAccelerationsCmd()
{
    a1 = 0;
    a2 = 0;
    a3 = 0;
}

LinearAccelerationsCmd::LinearAccelerationsCmd(float a1, float a2, float a3)
{
    this->a1 = a1;
    this->a2 = a2;
    this->a3 = a3;
}

LinearSpeedsCmd::LinearSpeedsCmd()
{
    a1 = 0;
    a2 = 0;
    a3 = 0;
}

LinearSpeedsCmd::LinearSpeedsCmd(float a1, float a2, float a3)
{
    this->a1 = a1;
    this->a2 = a2;
    this->a3 = a3;
}

LinearCoordinatesCmd::LinearCoordinatesCmd()
{
    a1 = 0;
    a2 = 0;
    a3 = 0;
}

LinearCoordinatesCmd::LinearCoordinatesCmd(float a1, float a2, float a3)
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
}
