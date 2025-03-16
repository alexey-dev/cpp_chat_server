#include <iostream>
#include <boost/asio.hpp>
#include "Client.hpp"
#include "SslClient.hpp"
#include "ClientArgumentsParser.hpp"

constexpr size_t MESSAGE_SIZE = 100;

int main(int _Argc, char* _Argv[])
{
  try
  {
    ClientArgumentsParser ArgumentsParser;
    if (!ArgumentsParser.Parse(_Argc, _Argv))
    {
      return 1;
    }

    const InputArguments &                       Arguments = ArgumentsParser.GetArguments();
    boost::asio::io_context                      IOContext;
    boost::asio::ip::tcp::resolver               Resolver(IOContext);
    boost::asio::ip::tcp::resolver::results_type Endpoints = Resolver.resolve(Arguments.Host, std::to_string(Arguments.Port));
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
