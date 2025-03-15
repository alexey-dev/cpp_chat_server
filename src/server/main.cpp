#include <iostream>
#include <boost/asio.hpp>
#include "Server.hpp"
#include "SslServer.hpp"
#include "ServerArgumentsParser.hpp"

int main(int _Argc, char * _Argv[])
{
  try
  {
    ServerArgumentsParser Parser;

    if (!Parser.Parse(_Argc, _Argv))
    {
      return 1;
    }

    const InputArguments &         Arguments = Parser.GetArguments();
    boost::asio::io_context        IOContext;
    boost::asio::ip::tcp::endpoint Endpoint(boost::asio::ip::tcp::v4(), Arguments.Port);
    SslServer                      MainServer(IOContext, Endpoint);

    MainServer.Start();
    IOContext.run();
  }
  catch (std::exception & _Exception)
  {
    std::cerr << "Thrown exception: " << _Exception.what() << std::endl;
  }

  return 0;
}
