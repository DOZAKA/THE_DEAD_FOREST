//
//  MessageTypes.hpp
//  TheDeadForest
//
//  Created by 남준현 on 2015. 11. 12..
//
//

#pragma once


namespace realtrick
{
    
    enum class MessageType : int
    {
        JOYSTICK_CONTROLED = 0,
        RELOAD_WEAPON,
        RUN_BACK_DEAD,
        RUN_FRONT_DEAD,
        SHOW_NEXT_ANIMATION_FRAME,
        SHOW_PREV_ANIMATION_FRAME
    };
        
    enum JoystickMessageTypes
    {
        NONE                            = 0x000000,
        MOVE                            = 0x000001,
        RUN                             = 0x000002,
        ATTACK_BEGAN                    = 0x000004,
        ATTACK_ENDED                    = 0x000008
    };
        
}
    
    
    
    
    
    
    
