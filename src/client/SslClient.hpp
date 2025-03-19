#ifndef SSL_CLIENT_HPP
#define SSL_CLIENT_HPP

#include <boost/asio/ssl.hpp>
#include "IClient.hpp"

class SslClient : public IClient
{
  public: // --- Constructor ---
    SslClient(boost::asio::io_context &                            _IOContext,
              boost::asio::ssl::context &                          _SslContext,
              const boost::asio::ip::tcp::resolver::results_type & _Endpoints);

  public: // --- Interface ---
    void Close() override;

  private: // --- Service ---
    bool VerifyCertificateCallback(bool                               _IsPreverified,
                                   boost::asio::ssl::verify_context & _Context);

    void DoHandshake();

    void DoConnect(const boost::asio::ip::tcp::resolver::results_type & _Endpoints) override;

    void DoWrite() override;

    void PostWrite() override;

    void DoReadDescriptor() override;

    void DoReadBody() override;

  private: // --- Member variables ---
    boost::asio::ssl::stream<boost::asio::ip::tcp::socket> m_Socket;
};

#endif // SSL_CLIENT_HPP