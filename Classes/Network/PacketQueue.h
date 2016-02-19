#pragma once
#include "Singleton.hpp"
#include <boost/lockfree/queue.hpp>
#include <stdexcept>
#include "PacketClass.h"

#define LOCK_FREE_QUEUE_SIZE 512

namespace realtrick
{
    namespace network
    {
        

        class PacketQueue : public Singleton<PacketQueue>
        {
            friend class Singleton<PacketQueue>;
        private:
            boost::lockfree::queue<Packet*> _queue;
            
            PacketQueue() : _queue(LOCK_FREE_QUEUE_SIZE)
            {}
            
        public:
            
            inline void push(Packet* const & t)
            {
                while (!_queue.push(t));
            }
            inline bool pop(Packet*& t)
            {
                if (isEmpty())
                {
                    return false;
                }
                return _queue.pop(t);
            }
            
            inline bool isEmpty() { return _queue.empty(); }
            
        };
    }
}