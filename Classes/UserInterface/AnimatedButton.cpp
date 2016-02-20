//
//  AnimatedButton.cpp
//  TheDeadForest-v2
//
//  Created by mac on 2016. 2. 21..
//
//

#include "AnimatedButton.hpp"

namespace realtrick
{
    namespace userinterface
    {
    
        using namespace cocos2d;
        
        AnimatedButton::AnimatedButton() :
        _currFrame(nullptr),
        _animInterval(0.0f),
        _isActive(false)
        {}
        
        
        AnimatedButton::~AnimatedButton()
        {
        }
        
        
        AnimatedButton* AnimatedButton::create(const char* normal, const char* selected, cocos2d::ui::Widget::TextureResType type)
        {
            AnimatedButton* ret = new (std::nothrow) AnimatedButton();
            if ( ret && ret->init(normal, selected, type) )
            {
                ret->autorelease();
                return ret;
            }
            CC_SAFE_DELETE(ret);
            return nullptr;
        }
        
        
        bool AnimatedButton::init(const char* normal, const char* selected, cocos2d::ui::Widget::TextureResType type)
        {
            if ( !Widget::init() )
                return false;
            
            loadTextures(normal, selected, "", type);
            
            _currFrame = Sprite::create();
            _currFrame->setPosition(Vec2(getContentSize() / 2.0f));
            addChild(_currFrame);
            
            setOpacity(0);
            
            return true;
        }
        
        
        void AnimatedButton::show()
        {
            //
            // case 1: 꺼져있는 상태일 때 > 애니메이션을 등록하고 재생시킨다.
            // case 2: 켜져있는 상태일 때 > 빠져나간다.
            // case 3: 켜지고 있는 상태일 때 > 빠져나간다.
            // case 4: 꺼지고 있는 상태일 때 > 뒤에 추가하고 끝나면 재생한다.
            //
            
            if ( _commandQueue.empty() || _commandQueue.front() != ActionCommand::SHOW )
                _commandQueue.push_back(ActionCommand::SHOW);
            
            if ( getActionManager()->getNumberOfRunningActionsInTarget(_currFrame) == 0 )
            {
                ActionCommand front = _commandQueue.front();
                _commandQueue.pop_front();
                
                Animation* animation = Animation::create();
                animation->setDelayPerUnit(_animInterval);
                if ( front == ActionCommand::SHOW )
                {
                    std::for_each(_animationFrameNames.cbegin(), _animationFrameNames.cend(), [animation](const std::string frameName){
                        animation->addSpriteFrameWithFile(frameName);
                    });
                }
                else
                {
                    std::for_each(_animationFrameNames.crbegin(), _animationFrameNames.crend(), [animation](const std::string frameName){
                        animation->addSpriteFrameWithFile(frameName);
                    });
                }
                
                _currFrame->runAction(Sequence::create(Animate::create(animation),
                                                       CallFunc::create([&]()
                                                                        {
                                                                            this->setOpacity(255);
                                                                            _currFrame->setVisible(false);
                                                                        }),
                                                       nullptr));
            }
            
        }
        
        
        void AnimatedButton::hide()
        {
            _commandQueue.push_back(ActionCommand::HIDE);
        }
        
    }
}









