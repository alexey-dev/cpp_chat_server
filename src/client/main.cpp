#include <iostream>
#include <boost/asio.hpp>
#include "Client.hpp"

int main(int _Argc, char* _Argv[])
{
  try
  {
    if (3 != _Argc)
    {
      std::cerr << "Format: client 'host' 'port'" << std::endl;
      return 1;
    }

    boost::asio::io_context IOContext;

    boost::asio::ip::tcp::resolver Resolver(IOContext);
    auto Endpoints = Resolver.resolve(_Argv[1], _Argv[2]);
    Client ClientMessenger(IOContext, Endpoints);

    std::thread Thread(
      [&IOContext]()
      {
        IOContext.run();
      });

    char Line[Message::MAX_BODY_SIZE + 1];
    while (std::cin.getline(Line, Message::MAX_BODY_SIZE + 1))
    {
      Message CurrentMessage;
      std::memcpy(CurrentMessage.GetBody(), Line, Message::MAX_BODY_SIZE);
      ClientMessenger.Write(CurrentMessage);
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
