#pragma once
#include <stdint.h>
#include <atomic>
#include <mutex>
#include <ctime>
#include <thread>
namespace realtrick
{
    namespace network
    {
        typedef uint64_t                object_t;
        typedef uint64_t                oid_t;
        typedef int32_t					packet_size_t;
        
        typedef uint32_t                stream_size_t;
        
        typedef std::time_t				tick_t;
        typedef std::thread				thread_t;
        typedef std::thread::id			threadId_t;
        
        typedef std::recursive_mutex	lock_t;
        typedef std::string				str_t;
        
#define SIZE_8				8
#define SIZE_64				64
#define SIZE_128			128
#define SIZE_256			256
#define SIZE_1024			1024
#define SIZE_4096			4096
#define SIZE_8192			8192
        
#define DB_PARAM_SIZE		8192
#define SOCKET_BUF_SIZE		1024*10
        
        typedef unsigned char		Byte;
        typedef char				Char;
        typedef int8_t              Int8;
        typedef uint8_t             UInt8;
        typedef int16_t				Int16;
        typedef uint16_t			UInt16;
        typedef int32_t				Int32;
        typedef uint32_t			UInt32;
        typedef int64_t				Int64;
        typedef uint64_t			UInt64;
        typedef float				Float;
    }
}