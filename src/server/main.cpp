#include <iostream>
#include <boost/asio.hpp>
#include "PlainServer.hpp"
#include "SslServer.hpp"
#include "ServerArgumentsParser.hpp"
#include "IServerBuilder.hpp"
#include "PlainServerBuilder.hpp"
#include "SslServerBuilder.hpp"

std::shared_ptr<IServer> CreatePlainServer(const std::shared_ptr<IServerBuilder> _Builder);

std::shared_ptr<IServer> CreateSslServer(const std::shared_ptr<IServerBuilder> _Builder);

std::shared_ptr<IServer> CreateServer(const InputArguments &    _Arguments,
                                      boost::asio::io_context & _IOContext);

int main(int _Argc, char * _Argv[])
{
  try
  {
    ServerArgumentsParser ArgumentsParser;

    if (!ArgumentsParser.Parse(_Argc, _Argv))
    {
      return 1;
    }

    boost::asio::io_context  IOContext;
    const InputArguments &   Arguments  = ArgumentsParser.GetArguments();
    std::shared_ptr<IServer> MainServer = CreateServer(Arguments, IOContext);

    MainServer->Start();
    IOContext.run();
  }
  catch (std::exception & _Exception)
  {
    std::cerr << "Thrown exception: " << _Exception.what() << std::endl;
  }

  return 0;
}

std::shared_ptr<IServer> CreatePlainServer(const std::shared_ptr<IServerBuilder> _Builder)
{
  _Builder->InitServerSetup();

  return _Builder->GetProduct();
}

std::shared_ptr<IServer> CreateSslServer(const std::shared_ptr<IServerBuilder> _Builder)
{
  _Builder->InitServerSetup();
  _Builder->InitSpecificSettings();

  return _Builder->GetProduct();
}

std::shared_ptr<IServer> CreateServer(const InputArguments &    _Arguments,
                                      boost::asio::io_context & _IOContext)
{
  if (_Arguments.IsSSLActive)
    return CreateSslServer(std::make_shared<SslServerBuilder>(_Arguments, _IOContext));
  else
    return CreatePlainServer(std::make_shared<PlainServerBuilder>(_Arguments, _IOContext));
}