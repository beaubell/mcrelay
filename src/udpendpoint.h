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
    udp::endpoint receiver_endpoint_;
    enum { max_length = 1024 };
    char data_[max_length];

public:
    UDPEndpoint(boost::asio::io_context& io_context,
                uint16_t localport,
                const boost::asio::ip::address& dest_address,
                uint16_t destport)
    : socket_(io_context, udp::endpoint(udp::v4(), localport)),
      sender_endpoint_(dest_address, destport)
    {
        do_receive();
    }

    void do_receive()
    {
        socket_.async_receive_from(
            boost::asio::buffer(data_, max_length), receiver_endpoint_,
                                   [this](boost::system::error_code ec, std::size_t bytes_recvd)
                                   {
                                       if (!ec && bytes_recvd > 0)
                                       {
                                           if (rEP)
                                               rEP->do_send(data_, bytes_recvd);
                                           
                                           do_receive();
                                       }
                                       else
                                       {
                                           do_receive();
                                       }
                                   });
    }
    
    void do_send(void* data, std::size_t length)
    {
        socket_.async_send_to(
            boost::asio::buffer(data, length), sender_endpoint_,
                              [this](boost::system::error_code /*ec*/, std::size_t /*bytes_sent*/)
                              {
                                  //do_receive();
                              });
    }
    

};

