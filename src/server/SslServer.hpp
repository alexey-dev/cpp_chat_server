#ifndef SSL_SERVER_HPP
#define SSL_SERVER_HPP

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include "IServer.hpp"
#include "SslServerBuilder.hpp"

class SslServer : public IServer
{
  friend class SslServerBuilder;

  public: // --- Constructor ---
    SslServer(boost::asio::io_context &              _IOContext,
              boost::asio::ssl::context::method      _SslMethod,
              const boost::asio::ip::tcp::endpoint & _Endpoint);

  private: // --- Service ---
    void DoAccept() override;

    void SetSslContextOptions(boost::asio::ssl::context_base::options _Options);

    void SetSslKeysPaths(const std::string & _PrivateKeyPath,
                         const std::string & _CertificatePath);

  private: // --- Member variables ---
    boost::asio::ssl::context m_SslContext;
};

#endif // SSL_SERVER_HPP