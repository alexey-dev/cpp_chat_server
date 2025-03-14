#ifndef SSL_SERVER_HPP
#define SSL_SERVER_HPP

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include "IServer.hpp"

class SslServer : public IServer
{
  public: // --- Constructor ---
    SslServer(boost::asio::io_context &              _IOContext,
           const boost::asio::ip::tcp::endpoint & _Endpoint);

  private: // --- Service ---
    void DoAccept() override;

  private: // --- Member variables ---
    boost::asio::ssl::context m_SslContext;
};

#endif // SSL_SERVER_HPP