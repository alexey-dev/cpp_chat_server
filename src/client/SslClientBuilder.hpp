#ifndef SSL_CLIENT_BUILDER_HPP
#define SSL_CLIENT_BUILDER_HPP

#include <boost/asio/ssl.hpp>
#include "IClientBuilder.hpp"

class SslClientBuilder : public IClientBuilder
{
  public: // --- Constructor/Destructor ---
    SslClientBuilder(const InputArguments &     _Arguments,
                     boost::asio::io_context &  _IOContext);

  public: // --- Interface ---
    void InitClientSetup() override;

    void InitSpecificSettings() override;

  private: // --- Member variables ---
    boost::asio::ssl::context m_SslContext;
};

#endif // SSL_CLIENT_BUILDER_HPP