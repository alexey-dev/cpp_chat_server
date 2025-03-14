#include <iostream>
#include <boost/asio.hpp>
#include "Client.hpp"
#include "SslClient.hpp"

constexpr size_t MESSAGE_SIZE = 100;

int main(int _Argc, char* _Argv[])
{
  try
  {
    if (3 != _Argc)
    {
      std::cerr << "Format: client 'host' 'port'" << std::endl;
      return 1;
    }

    boost::asio::io_context                      IOContext;
    boost::asio::ip::tcp::resolver               Resolver(IOContext);
    boost::asio::ip::tcp::resolver::results_type Endpoints = Resolver.resolve(_Argv[1], _Argv[2]);
    boost::asio::ssl::context                    SslContext(boost::asio::ssl::context::sslv23);

    SslContext.load_verify_file("sslkeys/selfsigned.crt");

    SslClient ClientMessenger(IOContext, SslContext, Endpoints);

    ClientMessenger.Start();

    std::thread Thread(
      [&IOContext]()
      {
        IOContext.run();
      });

    char Line[MESSAGE_SIZE + 1];

    while (std::cin.getline(Line, MESSAGE_SIZE))
    {
      ClientMessenger.WriteText(Line);
    }

    ClientMessenger.Close();
    Thread.join();
  }
  catch (std::exception & _Exception)
  {
    std::cerr << "Exception thrown: " << _Exception.what() << std::endl;
  }

  return 0;
}
