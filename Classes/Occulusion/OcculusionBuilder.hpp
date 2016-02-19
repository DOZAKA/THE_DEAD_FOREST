//
//  OcculusionBuilder.hpp
//  TheDeadForest
//
//  Created by 남준현 on 2015. 12. 5..
//
//

#pragma once

#include "ClipperWrapper.hpp"

#define SEGMENT_LENGTH      10000

namespace realtrick
{
    
    class OcculusionBuilder : public cocos2d::Ref
    {
    
    public:
        
        struct FieldOfView
        {
            bool isEnable;
            cocos2d::Vec2 heading;
            float entryDegree;
            float aroundCircleRadius;
            int aroundCircleSlice;
            
            FieldOfView() = default;
            virtual ~FieldOfView() = default;
            FieldOfView(bool f, const cocos2d::Vec2& h, float d, float r, int s) :
            isEnable(f),
            heading(h),
            entryDegree(d),
            aroundCircleRadius(r),
            aroundCircleSlice(s)
            {}
        };
        
    public:
        
        enum class WindingOrder { CW, CCW };

    public:
        
        static OcculusionBuilder* create(cocos2d::Node* renderTarget, const cocos2d::Size& visibleSize);
        
        void setWindingOrder(WindingOrder order)                { _windingOrder = order; }
        
        void setShadowColor(const cocos2d::Color4F& color)      { _shadowColor = color; }

        void setVisibleColor(const cocos2d::Color4F& color)     { _visibleColor = color; }

        void setCameraMask(cocos2d::CameraFlag flag)            { _cameraMask = flag;  _texture->setCameraMask((unsigned short)_cameraMask); }
        
        void setBlendFunc(const cocos2d::BlendFunc& blendFunc)  { _texture->getSprite()->setBlendFunc(blendFunc); }
        
        cocos2d::Texture2D* getOcculusionTexture() const        { return _texture->getSprite()->getTexture(); }
        
        void invalidateTexture(const cocos2d::Vec2& worldPos, const std::vector<Polygon>& polygons, const cocos2d::Size& boundarySize, const FieldOfView& fov);

        cocos2d::RenderTexture* getRenderTexture() const        { return _texture; }
        
        void setDebugNode(cocos2d::DrawNode* debugNode)         { _debugNode = debugNode; }
        
        cocos2d::DrawNode* getDebugNode() const                 { return _debugNode; }
        
    private:
        
        cocos2d::RenderTexture*                 _texture;
        
        cocos2d::Node*                          _target;
        
        cocos2d::DrawNode*                      _dNode;
        
        std::vector<Polygon>                    _polygons;
        
        cocos2d::Rect                           _boundary;
        
        cocos2d::Color4F                        _shadowColor;
        
        cocos2d::Color4F                        _visibleColor;
        
        WindingOrder                            _windingOrder;
        
        cocos2d::Vec2                           _eyePos;
        
        cocos2d::CameraFlag                     _cameraMask;
        
        cocos2d::DrawNode*                      _debugNode;
        
        FieldOfView                             _fov;
        
    private:
        
        bool init(cocos2d::Node* renderTarget, const cocos2d::Size& visibleSize);
        
        OcculusionBuilder();
        
        virtual ~OcculusionBuilder();
        
        inline bool _isVisibleWall(const Segment& wall) const;
        
        inline int  _hashFunc(const cocos2d::Vec2& p) const;
        
        inline bool _isOneHitVertex(const std::vector<Segment>& walls, const cocos2d::Vec2& vert) const;
        
        inline cocos2d::Vec2 _getClosestIntersectPointToWall(const std::vector<Segment>& walls, const Segment& seg) const;
        
        inline cocos2d::Vec2 _worldToLocal(const cocos2d::Vec2& point);

    };
    
}

#include "OcculusionBuilder.inl"






















