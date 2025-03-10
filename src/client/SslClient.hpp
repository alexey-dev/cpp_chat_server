#ifndef SSL_CLIENT_HPP
#define SSL_CLIENT_HPP

#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include "IClient.hpp"
#include "../common/Message.hpp"
#include "../common/MessageBuilder.hpp"
#include "../common/MessageBlock.hpp"
#include <queue>
#include <map>

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