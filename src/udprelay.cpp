#include "relayendpoint.h"
#include "mcendpoint.h"
#include "udpendpoint.h"

#include <array>
#include <iostream>
#include <string>
#include <boost/asio.hpp>

//constexpr short multicast_port = 6969;


int main(int argc, char* argv[])
{
  try
  {
    if (argc != 6)
    {
      std::cerr << "Usage: udprelay <listen_address> <multicast_address> <multicast_port> <udp_listen_port> <remote_udp_address> <remote_udp_port>\n";
      std::cerr << "  For IPv4, try:\n";
      std::cerr << "    receiver 0.0.0.0 239.2.3.1 6969 10001 10.10.202.78 10000\n";
      std::cerr << "  For IPv6, try:\n";
      std::cerr << "    receiver 0::0 ff31::8000:1234\n";
      return 1;
    }

    boost::asio::io_context io_context;
    MCEndpoint ep_mc(io_context,
        boost::asio::ip::make_address(argv[1]),
        boost::asio::ip::make_address(argv[2]),
        strtoul(argv[3], 0 , 10)
        );
    
    UDPEndpoint ep_edp(io_context,
                 strtoul(argv[4], 0 , 10),
                 boost::asio::ip::make_address(argv[5]),
                 strtoul(argv[6], 0 , 10)
    );
    
    // Setup relays
    ep_edp.setRelay(&ep_mc);
    ep_mc.setRelay(&ep_edp);

    io_context.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
