
#include"Stream.h"

namespace realtrick
{
    namespace network
    {
        Stream::Stream()
        {
            this->initialize();
        }
        
        Stream::Stream(unsigned char* stream, size_t size)
        {
            this->initialize();
            this->set(stream, size);
        }
        
        void Stream::initialize()
        {
            _readPt = 0;
            _offset = 0;
            memset(&_stream, 0, sizeof(_stream));
        }
        
        unsigned char* Stream::data()
        {
            return _stream.data();
        }
        
        size_t Stream::size()
        {
            return _offset;
        }
        
        void Stream::operator=(Stream& stream)
        {
            this->set(stream.data(), stream.size());
        }
        
        void Stream::set(unsigned char* data, size_t size)
        {
            this->_offset = size;
            memcpy(this->_stream.data(), (void*)data, size);
        }
        
        // write
        //--------------------------------------------------------------------------//
        bool Stream::checkWriteBound(size_t len)
        {
            if (_offset + len > sizeof(_stream))
            {
                
                return false;
            }
            return true;
        }
        
        void Stream::operator<<(const bool& value)
        {
            STREAM_WRITE(value);
        }
        void Stream::operator<<(const Int8& value)
        {
            STREAM_WRITE(value);
        }
        void Stream::operator<<(const UInt8& value)
        {
            STREAM_WRITE(value);
        }
        void Stream::operator<<(const Int16& value)
        {
            STREAM_WRITE(value);
        }
        void Stream::operator<<(const UInt16& value)
        {
            STREAM_WRITE(value);
        }
        void Stream::operator<<(const Int32& value)
        {
            STREAM_WRITE(value);
        }
        void Stream::operator<<(const UInt32& value)
        {
            STREAM_WRITE(value);
        }
        void Stream::operator<<(const Int64& value)
        {
            STREAM_WRITE(value);
        }
        void Stream::operator<<(const UInt64& value)
        {
            STREAM_WRITE(value);
        }
        void Stream::operator<<(const cocos2d::Vec2& value)
        {
            STREAM_WRITE(value);
        }
        void Stream::operator<<(const str_t &value)
        {
            *this << (Int32)value.length();
            for (auto i : value)
            {
                *this << i;
            }
        }
        // read
        //--------------------------------------------------------------------------//
        
        bool Stream::checkReadBound(size_t len)
        {
            if (_readPt + len > _offset)
            {
                
                return false;
            }
            return true;
        }
        
        void Stream::read(void* retVal, size_t len)
        {
            memcpy(retVal, (void*)(_stream.data() + _readPt), len);
            _readPt += len;
        }
        
        void Stream::operator>>(bool* retVal)
        {
            STREAM_READ(bool, retVal);
        }
        void Stream::operator>>(Int8* retVal)
        {
            STREAM_READ(Int8, retVal);
        }
        void Stream::operator>>(UInt8* retVal)
        {
            STREAM_READ(UInt8, retVal);
        }
        void Stream::operator>>(Int16* retVal)
        {
            STREAM_READ(Int16, retVal);
        }
        void Stream::operator>>(UInt16* retVal)
        {
            STREAM_READ(UInt16, retVal);
        }
        void Stream::operator>>(Int32* retVal)
        {
            STREAM_READ(Int32, retVal);
        }
        void Stream::operator>>(UInt32* retVal)
        {
            STREAM_READ(UInt32, retVal);
        }
        void Stream::operator>>(Int64* retVal)
        {
            STREAM_READ(Int64, retVal);
        }
        void Stream::operator>>(UInt64* retVal)
        {
            STREAM_READ(UInt64, retVal);
        }
        void Stream::operator>>(cocos2d::Vec2* retVal)
        {
            STREAM_READ(cocos2d::Vec2, retVal);
        }
        
        void Stream::operator>>(str_t* retVal)
        {
            Int32 size;
            *this >> &size;
            if (this->checkReadBound(size) == false)
            {
                return;
            }
            
            char* buf = new char[size + 1];
            this->read((void*)(buf), size * sizeof(char));
            buf[size] = '\0';
            
            retVal->clear();
            *retVal = buf;
            
            delete buf;
            
        }
    }
}