#include "Network.h"
#include "PacketFactory.h"
#include "PacketQueue.h"

#include <iostream>
#include <boost/asio.hpp>

namespace realtrick
{
    namespace network
    {
        Network::Network()
        :	 _ptrService(new boost::asio::io_service),
        _ioService(*_ptrService),
        _socket(_ioService),
        _isConnect(false)
        {
            tcp::resolver resolver(_ioService);
            auto endpoint_iterator = resolver.resolve({ "211.189.127.155", "9000" });
            doConnect(endpoint_iterator);
            
            
            _thread = std::make_shared<std::thread>(&Network::start, this);
            
        }
        Network::~Network()
        {
            close();
        }
        
        
        void Network::start()
        {
            try
            {
                _ioService.run();
            }
            catch (std::exception& e)
            {
                std::cerr << "Exception: " << e.what() << "\n";
            }
        }
        
        
        
        //*******************************************************************************************************************************
        
        
        //*******************************************************************************************************************************
        
        
        void Network::close()
        {
            _socket.close();
        }
        
        
        void Network::doConnect(tcp::resolver::iterator endpoint_iterator)
        {
            boost::asio::async_connect(_socket, endpoint_iterator,
                                       [this](boost::system::error_code ec, tcp::resolver::iterator)
                                       {
                                           if (!ec)
                                           {
                                               //boost::asio::ip::tcp::no_delay option(true);
                                               //_socket.set_option(option);
                                    
                                               doReadHeader();
                                                _isConnect = true;
                                           }
                                       });
        }
        
        void Network::doReadHeader()
        {
            boost::asio::async_read(_socket,
                                    boost::asio::buffer(&_packetLength, sizeof(_packetLength)),
                                    [this](boost::system::error_code ec, std::size_t /*length*/)
                                    {
                                        if (!ec)
                                        {
                                            doReadBody();
                                        }
                                        else
                                        {
                                            _socket.close();
                                        }
                                    });
        }
        void Network::doReadBody()
        {
            boost::asio::async_read(_socket,
                                    boost::asio::buffer(_ioData.data(), _packetLength),
                                    [this](boost::system::error_code ec, std::size_t /*length*/)
                                    {
                                        if (!ec)
                                        {
                                            stream_size_t offset = 0;
                                            PacketType type[1] = { (PacketType)0, };
                                            memcpy((void*)type, (void*)_ioData.data(), sizeof(type));
                                            offset += sizeof(type);
                                            Packet* packet = PacketFactory::getInstance().getPacket(type[0]);
                                            
                                            Stream stream((unsigned char*)(_ioData.data() + offset), _packetLength - offset);
                                            packet->decode(stream);
                                            
                                            PacketQueue::getInstance().push(packet);
                                            
                                            doReadHeader();
                                        }
                                        else
                                        {
                                            _socket.close();
                                        }
                                    });
        }
        
        void Network::sendPacket(Packet* packet)
        {
            Stream stream;
            packet->encode(stream);
            
            packet_size_t offset = 0;
            std::array<char, SOCKET_BUF_SIZE> buffer;
            packet_size_t packetLen[1] = { (packet_size_t)stream.size(), };
            
            memcpy(buffer.data() + offset, (void*)packetLen, sizeof(packetLen));
            offset += sizeof(packetLen);
            memcpy(buffer.data() + offset, stream.data(), packetLen[0]);
            offset += (packet_size_t)stream.size();
            
            doWrite(buffer.data(), offset);
        }
        
        void Network::doWrite(char* packet, int size)
        {
            //	std::cout << "send packet size : " << size << std::endl;
            boost::asio::async_write(_socket,
                                     boost::asio::buffer(packet, size),
                                     [this](boost::system::error_code ec, std::size_t /*length*/)
                                     {
                                         if (!ec)
                                         {
                                             
                                         }
                                         else
                                         {
                                             
                                         }
                                     });
            
            
            
            
        }
    }
}