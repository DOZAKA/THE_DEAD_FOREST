#pragma once
#include <queue>
#include <array>
#include "Type.h"
#include "cocos2d.h"

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
            Stream(unsigned char* stream, stream_size_t size);
            void initialize();
            
            unsigned char* data();
            stream_size_t size();
            
            void operator=(Stream& stream);
            void set(unsigned char* stream, stream_size_t size);
            
            //write
            //-------------------------------------------------------------------------------------//
            bool checkWriteBound(stream_size_t len);
            
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

            void operator<<(const str_t &value);
            
            // read
            //--------------------------------------------------------------------------
            
            bool checkReadBound(stream_size_t len);
            void read(void* retVal, stream_size_t len);
            
            #define STREAM_READ(type, retVal)				\
            stream_size_t size = sizeof(type);					\
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
                UInt64 size;
                *this >> &size;
                
                for (stream_size_t i = 0; i < size; ++i)
                {
                    T tmp;
                    *this >> &tmp;
                    retVal->push_back(tmp);
                }
            }

            void operator>>(str_t* retVal);
            
        };
    }
}
