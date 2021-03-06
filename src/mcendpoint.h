#pragma once

#include <array>
#include <iostream>
#include <string>
#include <boost/asio.hpp>

class MCEndpoint : public RelayEndpoint
{
private:
    uint16_t port_;
    boost::asio::ip::udp::endpoint mcendpoint_;
    boost::asio::ip::udp::socket socket_;
    boost::asio::ip::udp::endpoint sender_endpoint_;
    std::array<char, 2048> data_;
    boost::asio::ip::address local_address_;
    
public:
    MCEndpoint(boost::asio::io_context& io_context,
             const boost::asio::ip::address& local_address,
             const boost::asio::ip::address& multicast_address,
             const uint16_t port)
    : socket_(io_context),
      port_(port),
      mcendpoint_(multicast_address, port),
      local_address_(local_address)
    {
        boost::asio::ip::address listen_address = boost::asio::ip::make_address("0.0.0.0");
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
    
    void do_send(void* data, size_t size) {
        
        std::cout << "Multicast Sending to: " << mcendpoint_ << " (len" << std::to_string(size) << ")" << std::endl;
        socket_.async_send_to(
            boost::asio::buffer(data, size), mcendpoint_,
                              [this](boost::system::error_code ec, std::size_t /*length*/)
                              {
                                  //if (!ec && message_count_ < max_message_count)
                                  //    do_timeout();
                                  if (ec)
                                      std::cerr << "Multicast send error: " << ec << std::endl;
                              });
    }
    
private:
    void do_receive()
    {
        socket_.async_receive_from(
            boost::asio::buffer(data_), sender_endpoint_,
                                   [this](boost::system::error_code ec, std::size_t length)
                                   {
                                       if (!ec)
                                       {
                                     
                                           //std::cout.write(data_.data(), length);
                                           //std::cout << std::endl;

                                           if ((sender_endpoint_.address() != local_address_) && rEP) {
                                               std::cout << "Multicast Receiving from: " << sender_endpoint_ << " (len:" << std::to_string(length) << ")" << std::endl;
                                               rEP->do_send(data_.data(), length);
                                               
                                           }

                                           do_receive();
                                       } else {
                                           std::cerr << "Multicast recv error: " << ec << std::endl;
                                           do_receive();
                                       }
                                   });
    }
    
};
