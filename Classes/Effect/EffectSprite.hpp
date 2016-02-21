//
//  EffectSprite.hpp
//  TheDeadForest
//
//  Created by mac on 2016. 2. 8..
//
//

#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"

namespace realtrick
{
    class EffectBase;
    
    class EffectSprite : public cocos2d::Sprite
    {
        
    public:
        
        static EffectSprite* create(const std::string& filename,
                                    cocos2d::ui::Widget::TextureResType texResType = cocos2d::ui::Widget::TextureResType::LOCAL);
        
        static EffectSprite* createWithTexture(cocos2d::Texture2D* texture);
        
        void setEffect(EffectBase* effect);
        
    protected:
        
        virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags) override;
        
        virtual ~EffectSprite();
        
    protected:
        
        EffectBase* _effect = nullptr;
        
    };
    
}









