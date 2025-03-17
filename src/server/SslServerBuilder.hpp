#ifndef SSL_SERVER_BUILDER_HPP
#define SSL_SERVER_BUILDER_HPP

#include <boost/asio/ssl.hpp>
#include "IServerBuilder.hpp"

class SslServerBuilder : public IServerBuilder
{
  public: // --- Constructor/Destructor ---
  SslServerBuilder(const InputArguments &    _Arguments,
                   boost::asio::io_context & _IOContext);

  public: // --- Interface ---
    void InitServerSetup() override;

    void InitSpecificSettings() override;
};

#endif // SSL_SERVER_BUILDER_HPP