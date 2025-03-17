#include <iostream>
#include <boost/asio.hpp>
#include "PlainClient.hpp"
#include "SslClient.hpp"
#include "ClientArgumentsParser.hpp"
#include "IClientBuilder.hpp"
#include "PlainClientBuilder.hpp"
#include "SslClientBuilder.hpp"

constexpr size_t MESSAGE_SIZE = 100;

std::shared_ptr<IClient> CreatePlainClient(const std::shared_ptr<IClientBuilder> _Builder);

std::shared_ptr<IClient> CreateSslClient(const std::shared_ptr<IClientBuilder> _Builder);

std::shared_ptr<IClient> CreateClient(const InputArguments &    _Arguments,
                                      boost::asio::io_context & _IOContext);

int main(int _Argc, char* _Argv[])
{
  try
  {
    ClientArgumentsParser ArgumentsParser;
    if (!ArgumentsParser.Parse(_Argc, _Argv))
    {
      return 1;
    }

    boost::asio::io_context  IOContext;
    const InputArguments &   Arguments       = ArgumentsParser.GetArguments();
    std::shared_ptr<IClient> ClientMessenger = CreateClient(Arguments, IOContext);

    ClientMessenger->Start();

    std::thread Thread(
      [&IOContext]()
      {
        IOContext.run();
      });

    char Line[MESSAGE_SIZE + 1];

    while (std::cin.getline(Line, MESSAGE_SIZE))
    {
      ClientMessenger->WriteText(Line);
    }

    ClientMessenger->Close();
    Thread.join();
  }
  catch (std::exception & _Exception)
  {
    std::cerr << "Exception thrown: " << _Exception.what() << std::endl;
  }

  return 0;
}

std::shared_ptr<IClient> CreatePlainClient(const std::shared_ptr<IClientBuilder> _Builder)
{
  _Builder->InitClientSetup();

  return _Builder->GetProduct();
}

std::shared_ptr<IClient> CreateSslClient(const std::shared_ptr<IClientBuilder> _Builder)
{
  _Builder->InitSpecificSettings();
  _Builder->InitClientSetup();

  return _Builder->GetProduct();
}

std::shared_ptr<IClient> CreateClient(const InputArguments &    _Arguments,
                                      boost::asio::io_context & _IOContext)
{
  if (_Arguments.IsSSLActive)
    return CreateSslClient(std::make_shared<SslClientBuilder>(_Arguments, _IOContext));
  else
    return CreatePlainClient(std::make_shared<PlainClientBuilder>(_Arguments, _IOContext));
}