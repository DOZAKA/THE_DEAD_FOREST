//
//  AnimatedButton.hpp
//  TheDeadForest
//
//  Created by mac on 2016. 1. 24..
//
//

#pragma once

#include "cocos2d.h"
#include "CocosGUI.h"

namespace realtrick
{
    
    class AnimatedButton : public cocos2d::ui::Button
    {
        
    public:
        
        static AnimatedButton* create(const std::string& normal, const std::string& selected, const std::vector<std::string>& frames, float delayPerUnit,
                                      cocos2d::ui::Widget::TextureResType texResType, cocos2d::ui::Widget::ccWidgetTouchCallback callback = nullptr);
        void setAnimationFrames(const std::vector<std::string>& framePaths, float delayPerUnit);
        void show();
        void hide();
        void forceShow();
        void forceHide();
        bool isShow() const { return _isShow; }
        void setDelayPerUnit(float delay) { _delayPerUnit = delay; }
        void setFrames(const std::vector<std::string>& framsPaths) { _frames.clear(); _frames = framsPaths; }
        int getFrameSize() const { return (int)_frames.size() ; }
        float getDelayPerUnit() const { return _delayPerUnit; }
        
    private:
        
        bool                        _isShow;
        cocos2d::Sprite*            _spriteForAnimate;
        std::vector<std::string>    _frames;
        float                       _delayPerUnit;
        int                         _currFrame;
        
    private:
        
        AnimatedButton();
        virtual ~AnimatedButton();
        bool init(const std::string& normal, const std::string& selected, const std::vector<std::string>& frames, float delayPerUnit,
                  cocos2d::ui::Widget::TextureResType texResType, cocos2d::ui::Widget::ccWidgetTouchCallback callback);
        
    };
    
}