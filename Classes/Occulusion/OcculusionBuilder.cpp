//
//  OcculusionBuilder.cpp
//  TheDeadForest
//
//  Created by 남준현 on 2015. 12. 5..
//
//

#include "OcculusionBuilder.hpp"

using namespace cocos2d;
using namespace std;

namespace realtrick
{
    
    OcculusionBuilder::OcculusionBuilder() :
    _texture(nullptr),
    _target(nullptr),
    _dNode(nullptr),
    _boundary(cocos2d::Rect::ZERO),
    _shadowColor(Color4F(0, 0, 0, 1)),
    _visibleColor(Color4F(1, 1, 1, 1)),
    _windingOrder(WindingOrder::CCW),
    _eyePos(Vec2::ZERO),
    _cameraMask(CameraFlag::DEFAULT),
    _debugNode(nullptr)
    {
    }
    
    
    OcculusionBuilder::~OcculusionBuilder()
    {
        CC_SAFE_RELEASE_NULL(_dNode);
    }
    
    
    OcculusionBuilder* OcculusionBuilder::create(Node* renderTarget, const Size& visibleSize)
    {
        OcculusionBuilder* ret = new (std::nothrow)OcculusionBuilder();
        if ( ret && ret->init(renderTarget, visibleSize) )
        {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
    
    
    bool OcculusionBuilder::init(Node* renderTarget, const Size& visibleSize)
    {
        if ( !renderTarget || visibleSize.width <= 0.0f || visibleSize.height <= 0.0f )
            return false;
        
        _target = renderTarget;
        
        _texture = RenderTexture::create(visibleSize.width, visibleSize.height);
        _target->addChild(_texture);
        
        _dNode = DrawNode::create();
        _dNode->setPosition(visibleSize / 2);
        _dNode->retain();
        
        return true;
    }
    
    
    void OcculusionBuilder::invalidateTexture(const cocos2d::Vec2& worldPos,
                                              const std::vector<Polygon>& polygons,
                                              const cocos2d::Size& boundarySize,
                                              const FieldOfView& fov)
    {
        _eyePos = worldPos;
        
        // 경계면 정점을 만든다.
        Polygon clipBoundary;
        
        //
        // (v2)               (v3)
        //   . --------------- .
        //   |     worldPos    |
        //   |        .        |
        //   |                 |
        //   . --------------- .
        // (v1)               (v4)
        //
        const int PAD = 0;
        Vec2 v1 = Vec2(worldPos.x - boundarySize.width / 2 + PAD, worldPos.y - boundarySize.height / 2 + PAD); // left bottom
        Vec2 v2 = Vec2(worldPos.x - boundarySize.width / 2 + PAD, worldPos.y + boundarySize.height / 2 - PAD); // left top
        Vec2 v3 = Vec2(worldPos.x + boundarySize.width / 2 - PAD, worldPos.y + boundarySize.height / 2 - PAD); // right top
        Vec2 v4 = Vec2(worldPos.x + boundarySize.width / 2 - PAD, worldPos.y - boundarySize.height / 2 + PAD); // right bottom
        
        if ( fov.isEnable )
        {
            // fov 를 적용한다면 시야각과 플레이어 주변 원 데이터를 이용해 클리핑 경계면을 만든다. ( CCW )
            //                                     *fov : field of view (시야각)
            //             (n + m)
            //   (1) . ---.---.---.-- . (n+4)
            //        \              /
            //         \            /
            //          \          /
            //           \        /
            //            \ fov  /
            //             \    /
            //           (2)'  '(n+3)
            //             . w  .
            //              '..'
            //          ( n 개의 정점 )
            //
            //
            
            // "1", "n + 4" vertex
            vector<Segment> boundaryWalls;
            boundaryWalls.push_back(Segment(v1, v2));
            boundaryWalls.push_back(Segment(v2, v3));
            boundaryWalls.push_back(Segment(v3, v4));
            boundaryWalls.push_back(Segment(v4, v1));
            
            Mat3 rotationMatrix;
            rotationMatrix.rotate(MATH_DEG_TO_RAD(fov.entryDegree/2));
            Vec2 leftDir = rotationMatrix.getTransformedVector(fov.heading);
            Segment leftRay = Segment(worldPos, worldPos + leftDir * SEGMENT_LENGTH);
            
            rotationMatrix.identity();
            rotationMatrix.rotate(MATH_DEG_TO_RAD(-fov.entryDegree/2));
            Vec2 rightDir = rotationMatrix.getTransformedVector(fov.heading);
            Segment rightRay = Segment(worldPos, worldPos + rightDir * SEGMENT_LENGTH);
            
            Vec2 leftIntersectPoint = _getClosestIntersectPointToWall(boundaryWalls, leftRay);
            Vec2 rightIntersectPoint = _getClosestIntersectPointToWall(boundaryWalls, rightRay);
            
            
            // "n + m" vertex
            std::vector<Vec2> belongPoints;
            if ( leftDir.cross(v1 - worldPos) < 0 && rightDir.cross(v1 - worldPos) > 0 ) belongPoints.push_back(v1);
            if ( leftDir.cross(v2 - worldPos) < 0 && rightDir.cross(v2 - worldPos) > 0 ) belongPoints.push_back(v2);
            if ( leftDir.cross(v3 - worldPos) < 0 && rightDir.cross(v3 - worldPos) > 0 ) belongPoints.push_back(v3);
            if ( leftDir.cross(v4 - worldPos) < 0 && rightDir.cross(v4 - worldPos) > 0 ) belongPoints.push_back(v4);
            
            std::sort(std::begin(belongPoints), std::end(belongPoints), [&, this](const Vec2& v1, const Vec2& v2){
                
                Vec2 tempV1 = (v1 - _eyePos).getNormalized();
                Vec2 tempV2 = (v2 - _eyePos).getNormalized();
                
                float angle1 = physics::getAngleFromAxis(tempV1, fov.heading);
                float angle2 = physics::getAngleFromAxis(tempV2, fov.heading);
                
                return angle1 > angle2;

            });
        
            
            // "2", "n + 3" vertex
            Vec2 leftCirclePoint = worldPos + leftDir * fov.aroundCircleRadius;
            Vec2 rightCirclePoint = worldPos + rightDir * fov.aroundCircleRadius;
            
            
            // "n" vertices
            std::vector<Vec2> circleVertices;
            int remainCircleDegree = 360 - fov.entryDegree;
            int sliceCount = std::max(fov.aroundCircleSlice, 10); // 최소 10개의 정점을 이용해 정점 n을 만든다.
            int degreePerLoop = remainCircleDegree / sliceCount;
            for(int i = 1 ; i < sliceCount ; ++ i)
            {
                Vec2 dir = (leftCirclePoint - worldPos).getNormalized();
                Mat3 rotateMatrix;
                rotateMatrix.rotate(MATH_DEG_TO_RAD(degreePerLoop * i));
                Vec2 rotatedPoint = worldPos + rotateMatrix.getTransformedVector(dir) * fov.aroundCircleRadius;
                circleVertices.push_back(Vec2(rotatedPoint));
            }
            
            // 구한 정점을 순서에 맞게 합친다. ( 1, 2, ... , n + 3, n + 4, n + m )
            clipBoundary.pushVertex(leftIntersectPoint);
            clipBoundary.pushVertex(leftCirclePoint);
            
            for(const auto& vert : circleVertices)
                clipBoundary.pushVertex(vert);
            
            clipBoundary.pushVertex(rightCirclePoint);
            clipBoundary.pushVertex(rightIntersectPoint);
            
            for(const auto& vert : belongPoints)
                clipBoundary.pushVertex(vert);
            
        }
        else
        {
            // fov를 적용하지 않는다면 영역 사이즈를 이용해 사각형 클리핑 경계면을 만든다. ( CCW )
            clipBoundary.pushVertex(v4);
            clipBoundary.pushVertex(v3);
            clipBoundary.pushVertex(v2);
            clipBoundary.pushVertex(v1);
        }
        
        
        // 폴리곤을 클리핑 한다. ( CCW )
        vector<Polygon> clippedPloygon = clipping::getClippedPolygons(polygons, clipBoundary);
        vector<Segment> visibleWalls;
        vector<Vec2> storedVert;
        
        
        // 클리핑된 도형에 대해 벽을 생성한다.
        for(const auto& polygon : clippedPloygon)
        {
            Polygon p = polygon;
            p.pushVertex(p.vertices.front());
            for(int i = 0 ; i < p.vertices.size() - 1 ; ++ i)
            {
                Segment wall = Segment(p.vertices[i], p.vertices[i + 1]);
                if ( _isVisibleWall(wall) )
                    visibleWalls.push_back(wall);
            }
        }
        
        
        // 경계면에 대해 벽을 생성.
        if ( _windingOrder == WindingOrder::CCW )
        {
            int vertSize = (int)clipBoundary.vertices.size();
            for(int i = 0 ; i < vertSize - 1 ; ++i )
            {
                Segment wall(clipBoundary.vertices[i], clipBoundary.vertices[i + 1]);
                visibleWalls.push_back(wall);
            }
            Segment wall(clipBoundary.vertices.back(), clipBoundary.vertices.front());
            visibleWalls.push_back(wall);
        }
//        else
//        {
//            for(int i = 0 ; i < clipBoundary.vertices.size() ; ++ i)
//            {
//                Segment wall(clipBoundary.vertices[i], clipBoundary.vertices[i + 1]);
//                visibleWalls.push_back(wall);
//            }
//            Segment wall(clipBoundary.vertices.back(), clipBoundary.vertices.front());
//            visibleWalls.push_back(wall);
//        }
        
        
        // 같은 정점을 제거한다.
        {
            std::unordered_map<int, bool> uniqueVertice;
            for(const auto &wall : visibleWalls)
            {
                int hash = _hashFunc(wall.start);
                if( uniqueVertice[hash] == false )
                {
                    storedVert.push_back(wall.start);
                    uniqueVertice[hash] = true;
                }
                
                hash = _hashFunc(wall.end);
                if( uniqueVertice[hash] == false )
                {
                    storedVert.push_back(wall.end);
                    uniqueVertice[hash] = true;
                }
            }
        }
        
        
        // 두 번 이상 충돌되는 점 모두제거.
        {
            storedVert.erase(remove_if(begin(storedVert), end(storedVert), [&, this](const Vec2& v){
                
                return !_isOneHitVertex(visibleWalls, v);
                
            }), end(storedVert));
        }
        
        
        // 각 정점으로 세 갈레로 광선을 쏴본 후 걸리는 부분을 추가한다.
        {
            int tempSize = (int)storedVert.size();
            for(int i = 0 ; i < tempSize; ++ i)
            {
                Mat3 rotMat;
                Vec2 direction, desti, closestVert;
                
                // left
                rotMat.identity();
                rotMat.rotate(CC_DEGREES_TO_RADIANS(0.05f));
                direction = rotMat.getTransformedVector(storedVert[i] - _eyePos).getNormalized();
                desti = _eyePos + direction * SEGMENT_LENGTH;
                closestVert = _getClosestIntersectPointToWall(visibleWalls, Segment(_eyePos, desti));
                
                if( (storedVert[i] - closestVert).getLengthSq() > 1.0f )
                    storedVert.push_back(closestVert);
                
                // right
                rotMat.identity();
                rotMat.rotate(-CC_DEGREES_TO_RADIANS(0.05f));
                direction = rotMat.getTransformedVector(storedVert[i] - _eyePos).getNormalized();
                desti = _eyePos + direction * SEGMENT_LENGTH;
                closestVert = _getClosestIntersectPointToWall(visibleWalls, Segment(_eyePos, desti));
                
                if( (storedVert[i] - closestVert).getLengthSq() > 1.0f )
                    storedVert.push_back(closestVert);
            }
        }
        
        
        // 점을 각도값으로 정렬.
        {
            std::sort(std::begin(storedVert), std::end(storedVert), [=](const Vec2& v1, const Vec2& v2) {
                
                Vec2 tempV1 = (v1 - _eyePos).getNormalized();
                Vec2 tempV2 = (v2 - _eyePos).getNormalized();
                
                float angle1 = physics::getAngleFromZero(tempV1);
                float angle2 = physics::getAngleFromZero(tempV2);
                
                return angle1 > angle2;
                
            });
        }
        
        
        // 삼각형 이어그리기
        {
            if( !storedVert.empty() ) storedVert.push_back(storedVert.front());
            
            _texture->beginWithClear(_shadowColor.r, _shadowColor.g, _shadowColor.b, _shadowColor.a);
            _dNode->clear();
            for(int i = 0 ; i < (int)storedVert.size() - 1 ; ++ i)
            {
                _dNode->drawTriangle(_worldToLocal(_eyePos), _worldToLocal(storedVert[i]), _worldToLocal(storedVert[i + 1]), _visibleColor);
            }
            _dNode->visit();
            _texture->end();
            
            if ( !storedVert.empty() ) storedVert.pop_back();
        }
        
        
        // 디버그용 
        if ( _debugNode->isVisible() )
        {
            // 보이는 벽 랜더링
            for(int i = 0 ; i < visibleWalls.size() ; ++ i)
            {
                _debugNode->drawSegment(_worldToLocal(visibleWalls[i].start), _worldToLocal(visibleWalls[i].end), 1.2f, Color4F::ORANGE);
            }
            
            // 광선, 정점 랜더링
            for( int i = 0 ; i < storedVert.size() ; ++ i)
            {
                _debugNode->drawSegment(Vec2::ZERO, _worldToLocal(storedVert[i]), 0.3f, Color4F::MAGENTA);
                _debugNode->drawDot(_worldToLocal(storedVert[i]), 3.0f, Color4F::RED);
            }
            
            // 클리핑 다각형 랜더링
            for( const auto& cp : clippedPloygon )
            {
                Polygon clipPoly = cp;
                if ( !clipPoly.vertices.empty() ) clipPoly.pushVertex(clipPoly.vertices.front());
                for(int i = 0 ; i < clipPoly.vertices.size() - 1; ++ i)
                {
                    _debugNode->drawSegment(_worldToLocal(clipPoly.vertices[i]), _worldToLocal(clipPoly.vertices[i+1]), 2.0f, Color4F::RED);
                }
                if ( !clipPoly.vertices.empty() ) clipPoly.vertices.pop_back();
            }

            // 경계면 랜더링
            if ( !clipBoundary.vertices.empty() ) clipBoundary.pushVertex(clipBoundary.vertices.front());
            for( int i = 0; i < clipBoundary.vertices.size() - 1 ; ++ i)
            {
                _debugNode->drawSegment(_worldToLocal(clipBoundary.vertices[i]), _worldToLocal(clipBoundary.vertices[i+1]), 0.5f, Color4F::GRAY);
            }
            if ( !clipBoundary.vertices.empty() ) clipBoundary.vertices.pop_back();
        }
    }
    
}












