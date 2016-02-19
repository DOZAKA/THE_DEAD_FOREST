#pragma once
#include <queue>
#include <array>
#include "Type.h"

namespace realtrick
{
    namespace network
    {
        class Stream
        {
        private:
            size_t _offset;
            size_t _readPt;
            std::array<unsigned char, SOCKET_BUF_SIZE> _stream;
        public:
            Stream();
            Stream(unsigned char* stream, size_t size);
            void initialize();
            
            unsigned char* data();
            size_t size();
            
            void operator=(Stream& stream);
            void set(unsigned char* stream, size_t size);
            
            //write
            //-------------------------------------------------------------------------------------//
            bool checkWriteBound(size_t len);
            
#define STREAM_WRITE(value)									\
            Int32 size = sizeof(value);									\
            if(this->checkWriteBound(size) == false)					\
            {															\
                return ;												\
            }															\
            memcpy((void*)(_stream.data() + _offset),					\
                   (const void*)&value, size);	\
            _offset += size;
            
            template<typename T>
            void operator<<(const T & value)
            {
                STREAM_WRITE(value);
            }
            
            void operator<<(const bool& value);
            void operator<<(const Int8& value);
            void operator<<(const UInt8& value);
            void operator<<(const Int16& value);
            void operator<<(const UInt16& value);
            void operator<<(const Int32& value);
            void operator<<(const UInt32& value);
            void operator<<(const Int64& value);
            void operator<<(const UInt64& value);
            void operator<<(const cocos2d::Vec2& value);
            
            template<typename T>
            void operator<<(const std::vector<T> &value)
            {
                *this << value.size();
                for (auto i : value)
                {
                    *this << i;
                }
            }
            
            
            template<typename T>
            void operator<<(std::queue<T> &value)
            {
                *this << value.size();
                while (!value.empty())
                {
                    T i = value.front();
                    value.pop();
                    *this << i;
                }
                
            }
            
            void operator<<(const str_t &value);
            
            // read
            //--------------------------------------------------------------------------
            
            bool checkReadBound(size_t len);
            void read(void* retVal, size_t len);
            
#define STREAM_READ(type, retVal)				\
            size_t size = sizeof(type);					\
            if (this->checkReadBound(size) == false)		\
            {											\
                return;									\
            }											\
            this->read((void*)(retVal), size);
            
            template<typename T>
            void operator>>(T* retVal)
            {
                STREAM_READ(T, retVal);
            }
            
            void operator>>(bool* retVal);
            void operator>>(Int8* retVal);
            void operator>>(UInt8* retVal);
            void operator>>(Int16* retVal);
            void operator>>(UInt16* retVal);
            void operator>>(Int32* retVal);
            void operator>>(UInt32* retVal);
            void operator>>(Int64* retVal);
            void operator>>(UInt64* retVal);
            void operator>>(cocos2d::Vec2* retVal);
            
            template<typename T>
            void operator>>(std::vector<T>* retVal)
            {
                size_t size;
                *this >> &size;
                
                for (size_t i = 0; i < size; ++i)
                {
                    T tmp;
                    *this >> &tmp;
                    retVal->push_back(tmp);
                }
            }
            
            template<typename T>
            void operator>>(std::queue<T>* retVal)
            {
                size_t size;
                *this >> &size;
                
                for (size_t i = 0; i < size; ++i)
                {
                    T tmp;
                    *this >> &tmp;
                    retVal->push(tmp);
                }
            }
            void operator>>(str_t* retVal);
            
        };
    }
}