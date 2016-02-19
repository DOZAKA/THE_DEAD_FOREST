/****************************************************************************
 Copyright (c) 2014 Chukong Technologies Inc.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

/*
 * based on cocos2d-x-3.6/tests/cpp-tests/Classes/ShaderTest/ShaderTest2.cpp
 * extended by Realtrick Games njh0602
 */

#include "EffectSprite.hpp"
#include "LightEffect.hpp"

using namespace cocos2d;

namespace realtrick
{
    
    EffectSprite *EffectSprite::create(const std::string& filename,
                                       ui::Widget::TextureResType texResType)
    {
        auto ret = new (std::nothrow) EffectSprite;
        if(ret && (texResType == ui::Widget::TextureResType::LOCAL) ? ret->initWithFile(filename) : ret->initWithSpriteFrameName(filename))
        {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_RELEASE(ret);
        return nullptr;
    }
    
    EffectSprite* EffectSprite::createWithTexture(cocos2d::Texture2D* texture)
    {
        auto ret = new (std::nothrow) EffectSprite;
        if(ret && ret->initWithTexture(texture))
        {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_RELEASE(ret);
        return nullptr;
    }
    
    void EffectSprite::setEffect(EffectBase *effect)
    {
        if( _effect != effect )
        {
            CC_SAFE_RELEASE(_effect);
            _effect = effect;
            CC_SAFE_RETAIN(_effect);
            setGLProgramState(_effect->getGLProgramState());
        }
    }
    
    
    void EffectSprite::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags)
    {
        if (_effect != nullptr)
        {
            _effect->prepareForRender(this);
        }
        Sprite::draw(renderer, transform, flags);
        renderer->render();
    }
    
    
    EffectSprite::~EffectSprite()
    {
        CC_SAFE_RELEASE(_effect);
    }
    
}









