#pragma once
#include <boost/asio.hpp>
#include <memory>
#include <array>
#include <thread>
#include "Singleton.hpp"
#include "Type.h"
#include "PacketClass.h"



namespace realtrick
{
    namespace network
    {
        class ClientGenerator : public Singleton<ClientGenerator>
        {
            friend class Singleton<ClientGenerator>;
        private:
            ClientGenerator() {
                _id = 32443;
            }
        public:
            UInt32 id()
            {
                return _id;
            }
            virtual ~ClientGenerator() = default;
        private:
            UInt32 _id;
        };
        
        
        
        
        using boost::asio::ip::tcp;
        class Network : public Singleton<Network>
        {
            
            friend class Singleton<Network>;
        private:
            Network();
        public:
            virtual ~Network();
            
            void close();
            void doConnect(tcp::resolver::iterator endpoint_iterator);
            void doReadHeader();
            void doReadBody();
            void sendPacket(Packet* packet);
            void doWrite(char* packet, int size);
            void start();
            inline bool isConnection() { return _isConnect; }
            
            
        private:
            bool                                        _isConnect;
            std::shared_ptr<std::thread>                _thread;
            std::shared_ptr<boost::asio::io_service>	_ptrService;
            boost::asio::io_service&					_ioService;
            tcp::socket									_socket;
            int32_t										_packetLength;
            std::array<char, SOCKET_BUF_SIZE>			_ioData;
        };
    }
}