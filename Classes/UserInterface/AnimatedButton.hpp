//
//  AnimatedButton.hpp
//  TheDeadForest-v2
//
//  Created by mac on 2016. 2. 21..
//
//

#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

namespace realtrick
{
    namespace userinterface
    {
        
        class AnimatedButton : public cocos2d::ui::Button
        {
            
        public:
            
            enum class ActionCommand { SHOW, HIDE };
            
        public:
            
            static AnimatedButton* create(const char* normal, const char* selected, cocos2d::ui::Widget::TextureResType type = cocos2d::ui::Widget::TextureResType::LOCAL);
            
            bool isActive() const { return (this->getOpacity() == 255); }
            
            void setAnimationFrameNames(const std::vector<std::string>& frameNames) { _animationFrameNames = frameNames; }
            
            void setAnimationInterval(float interval) { _animInterval = interval; }
            
            float getAnimationInterval() const { return _animInterval; }
            
            void show();
            
            void hide();
            
        private:
            
            std::vector<std::string>                _animationFrameNames;
            
            cocos2d::Sprite*                        _currFrame;
            
            float                                   _animInterval;
            
            std::list<ActionCommand>                _commandQueue;
            
        private:
            
            AnimatedButton();
            
            virtual ~AnimatedButton();
            
            bool init(const char* normal, const char* selected, cocos2d::ui::Widget::TextureResType type);
            
        };
    }
}









