#pragma once

#include "relayendpoint.h"

#include <cstdlib>
#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

class UDPEndpoint : public RelayEndpoint
{
private:
    udp::socket socket_;
    udp::endpoint sender_endpoint_;
    enum { max_length = 1024 };
    char data_[max_length];

public:
    UDPEndpoint(boost::asio::io_context& io_context,
           const boost::asio::ip::address& dest_address,
           uint16_t port)
    : socket_(io_context, udp::endpoint(udp::v4(), port))
    {
        do_receive();
    }

    void do_receive()
    {
        socket_.async_receive_from(
            boost::asio::buffer(data_, max_length), sender_endpoint_,
                                   [this](boost::system::error_code ec, std::size_t bytes_recvd)
                                   {
                                       if (!ec && bytes_recvd > 0)
                                       {
                                           do_send(bytes_recvd);
                                       }
                                       else
                                       {
                                           do_receive();
                                       }
                                   });
    }
    
    void do_send(std::size_t length)
    {
        socket_.async_send_to(
            boost::asio::buffer(data_, length), sender_endpoint_,
                              [this](boost::system::error_code /*ec*/, std::size_t /*bytes_sent*/)
                              {
                                  do_receive();
                              });
    }
    

};

