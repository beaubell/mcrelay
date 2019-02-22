#pragma once

#include <array>
#include <iostream>
#include <string>
#include <boost/asio.hpp>

class MCEndpoint : public RelayEndpoint
{
private:
    uint16_t port_;
    
public:
    MCEndpoint(boost::asio::io_context& io_context,
             const boost::asio::ip::address& listen_address,
             const boost::asio::ip::address& multicast_address,
             const uint16_t port)
    : socket_(io_context),
      port_(port)
    {
        // Create the socket so that multiple may be bound to the same address.
        boost::asio::ip::udp::endpoint listen_endpoint(
            listen_address, port_);
        socket_.open(listen_endpoint.protocol());
        socket_.set_option(boost::asio::ip::udp::socket::reuse_address(true));
        socket_.bind(listen_endpoint);
        
        // Join the multicast group.
        socket_.set_option(
            boost::asio::ip::multicast::join_group(multicast_address));
        
        do_receive();
    }
    
    //send()
    
private:
    void do_receive()
    {
        socket_.async_receive_from(
            boost::asio::buffer(data_), sender_endpoint_,
                                   [this](boost::system::error_code ec, std::size_t length)
                                   {
                                       if (!ec)
                                       {
                                           std::cout.write(data_.data(), length);
                                           std::cout << std::endl;
                                           
                                           do_receive();
                                       }
                                   });
    }
    
    boost::asio::ip::udp::socket socket_;
    boost::asio::ip::udp::endpoint sender_endpoint_;
    std::array<char, 1024> data_;
};
