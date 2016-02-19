//
//  Mat3.cpp
//  TheDeadForest
//
//  Created by 남준현 on 2015. 11. 12..
//  
//

#include "Mat3.hpp"

namespace realtrick
{
    
    void Mat3::_copy(const Mat3& copy)
    {
        _11 = copy._11;         _12 = copy._12;         _13 = copy._13;
        _21 = copy._21;         _22 = copy._22;         _23 = copy._23;
        _31 = copy._31;         _32 = copy._32;         _33 = copy._33;
    }
    
    void Mat3::_multiply(const Mat3& rhs)
    {
        Mat3 temp(*this);
        _11 = (temp._11 * rhs._11) + (temp._12 * rhs._21) + (temp._13 * rhs._31);
        _12 = (temp._11 * rhs._12) + (temp._12 * rhs._22) + (temp._13 * rhs._32);
        _13 = (temp._11 * rhs._13) + (temp._12 * rhs._23) + (temp._13 * rhs._33);
        
        _21 = (temp._21 * rhs._11) + (temp._22 * rhs._21) + (temp._23 * rhs._31);
        _22 = (temp._21 * rhs._12) + (temp._22 * rhs._22) + (temp._23 * rhs._32);
        _23 = (temp._21 * rhs._13) + (temp._22 * rhs._23) + (temp._23 * rhs._33);

        _31 = (temp._31 * rhs._11) + (temp._32 * rhs._21) + (temp._33 * rhs._31);
        _32 = (temp._31 * rhs._12) + (temp._32 * rhs._22) + (temp._33 * rhs._32);
        _33 = (temp._31 * rhs._13) + (temp._32 * rhs._23) + (temp._33 * rhs._33);
    }
    
    Mat3::Mat3()
    {
        identity();
    }
    
    Mat3::Mat3(const Mat3& copy)
    {
        _copy(copy);
    }
    
    Mat3& Mat3::operator=(const Mat3& rhs)
    {
        if(this == &rhs)
            return *this;
        _copy(rhs);
        return *this;
    }
    
    void Mat3::identity()
    {
        _11 = 1.0f;     _12 = 0.0f;     _13 = 0.0f;
        _21 = 0.0f;     _22 = 1.0f;     _23 = 0.0f;
        _31 = 0.0f;     _32 = 0.0f;     _33 = 1.0f;
    }
    
    void Mat3::scale(float scale)
    {
        Mat3 scaleMat;
        scaleMat._11 = scaleMat._22  = scale;
        _multiply(scaleMat);
    }
    
    void Mat3::scale(float xScale, float yScale)
    {
        Mat3 scaleMat;
        scaleMat._11 = xScale;
        scaleMat._22 = yScale;
        _multiply(scaleMat);
    }
    
    void Mat3::scale(const cocos2d::Vec2& scale)
    {
        Mat3 scaleMat;
        scaleMat._11 = scale.x;
        scaleMat._22 = scale.y;
        _multiply(scaleMat);
    }
    
    
    void Mat3::rotate(float radian)
    {
        Mat3 rotateMat;
        rotateMat._11 = cos(radian); rotateMat._12 = sin(radian);
        rotateMat._21 = -sin(radian); rotateMat._22 = cos(radian);
        _multiply(rotateMat);
    }
    
    
    void Mat3::rotate(const cocos2d::Vec2& heading, const cocos2d::Vec2& side)
    {
        Mat3 rotateMat;
        rotateMat._11 = heading.x;      rotateMat._12 = heading.y;      rotateMat._13 = 0.0f;
        rotateMat._21 = side.x;         rotateMat._22 = side.y;         rotateMat._23 = 0.0f;
        rotateMat._31 = 0.0f;           rotateMat._32 = 0.0f;           rotateMat._33 = 1.0f;
        _multiply(rotateMat);
    }
    
    void Mat3::translate(const cocos2d::Vec2& trans)
    {
        Mat3 transMat;
        transMat._31 = trans.x;
        transMat._32 = trans.y;
        _multiply(transMat);
    }
    
    cocos2d::Vec2 Mat3::getTransformedVector(const cocos2d::Vec2& v)
    {
        cocos2d::Vec2 ret;
        ret.x = (v.x * _11) + (v.y * _21) + _31;
        ret.y = (v.x * _12) + (v.y * _22) + _32;
        return ret;
    }
    
    std::vector<cocos2d::Vec2> Mat3::getTransformedVector(std::vector<cocos2d::Vec2> v)
    {
        std::vector<cocos2d::Vec2> ret;
        for( auto &d : v)
        {
            cocos2d::Vec2 temp;
            temp.x = (d.x * _11) + (d.y * _21) + _31;
            temp.y = (d.x * _12) + (d.y * _22) + _32;
            ret.push_back(temp);
        }
        return ret;
    }

}








