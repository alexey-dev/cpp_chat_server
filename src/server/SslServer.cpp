#include "SslServer.hpp"
#include "SslChatUser.hpp"

// --- Constructor ---
SslServer::SslServer(boost::asio::io_context &              _IOContext,
                     const boost::asio::ip::tcp::endpoint & _Endpoint) :
  IServer     (_IOContext, _Endpoint),
  m_SslContext(boost::asio::ssl::context::sslv23)
{
  m_SslContext.set_options(boost::asio::ssl::context::default_workarounds | boost::asio::ssl::context::no_sslv2);
  m_SslContext.use_certificate_chain_file("sslkeys/selfsigned.crt");
  m_SslContext.use_private_key_file("sslkeys/private.key", boost::asio::ssl::context::pem);
}

// --- Service ---
void SslServer::DoAccept()
{
  m_Acceptor.async_accept(
    [this](boost::system::error_code _ErrorCode,
           boost::asio::ip::tcp::socket _Socket)
    {
      if (!_ErrorCode)
      {
        std::shared_ptr<SslChatUser> User = std::make_shared<SslChatUser>(
          boost::asio::ssl::stream<boost::asio::ip::tcp::socket>(std::move(_Socket), m_SslContext),
          m_ChatSpace);

        m_ChatSpace.JoinUser(User);
        User->Start();
      }

      DoAccept();
    });
}