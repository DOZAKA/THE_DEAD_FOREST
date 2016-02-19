#pragma once
#include "Type.h"


namespace realtrick
{
    namespace network
    
    {
        enum class PacketType : Int64{
            /*0*/ E_C_REQ_EXIT = 0,
            /*1*/ E_S_ANS_EXIT = 1,
            /*2*/ E_I_NOTIFY_TERMINAL = 2,
            /*3*/ E_S_REQ_HEARTBEAT = 3,
            /*4*/ E_C_ANS_HEARTBEAT = 4,
            /*5*/ E_S_NOTIFY_FIXED_UPDATE = 5,
            /*6*/ E_S_NOTIFY_FIXED_UPDATE_BUNCH = 6,
            /*7*/ E_C_REQ_REGIST = 7,
            /*8*/ E_S_NOTIFY_STARTPOINT = 8,
            /*9*/ E_S_BROADCAST_STARTPOINT = 9,
            /*10*/ E_S_NOTIFY_GAMESTART = 10,
            /*11*/ E_C_REQ_JOYSTICK_MOVE_KEYDOWN = 11,
            /*12*/ E_S_BROADCAST_JOYSTICK_MOVE_KEYDOWN = 12,
            /*13*/ E_C_REQ_JOYSTICK_MOVE_KEYUP = 13,
            /*14*/ E_S_BROADCAST_JOYSTICK_MOVE_KEYUP = 14,
            /*15*/ E_C_REQ_JOYSTICK_DOUBLE_MOVE_KEYDOWN = 15,
            /*16*/ E_S_BROADCAST_JOYSTICK_DOUBLE_MOVE_KEYDOWN = 16,
            /*17*/ E_C_REQ_JOYSTICK_DOUBLE_MOVE_KEYUP = 17,
            /*18*/ E_S_BROADCAST_JOYSTICK_DOUBLE_MOVE_KEYUP = 18,
            /*19*/ E_C_REQ_JOYSTICK_MOVING_CHANGE = 19,
            /*20*/ E_S_BROADCAST_JOYSTICK_MOVING_CHANGE = 20,
            /*21*/ E_C_REQ_BEZEL_MOVE_KEYDOWN = 21,
            /*22*/ E_S_BROADCAST_BEZEL_MOVE_KEYDOWN = 22,
        };
    }
}