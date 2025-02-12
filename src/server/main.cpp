#include <iostream>
#include <boost/asio.hpp>
#include "Server.hpp"

int main(int _Argc, char * _Argv[])
{
  try
  {
    if (2 != _Argc)
    {
      std::cerr << "Format: server 'port'" << std::endl;
      return 1;
    }

    boost::asio::io_context        IOContext;
    boost::asio::ip::tcp::endpoint Endpoint(boost::asio::ip::tcp::v4(), std::atoi(_Argv[1]));
    Server                         MainServer(IOContext, Endpoint);

    IOContext.run();
  }
  catch (std::exception & _Exception)
  {
    std::cerr << "Thrown exception: " << _Exception.what() << std::endl;
  }

  return 0;
}
