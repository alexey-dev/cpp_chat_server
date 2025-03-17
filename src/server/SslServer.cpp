#include "SslServer.hpp"
#include "SslChatUser.hpp"

// --- Constructor ---
SslServer::SslServer(boost::asio::io_context &              _IOContext,
                     boost::asio::ssl::context::method      _SslMethod,
                     const boost::asio::ip::tcp::endpoint & _Endpoint) :
  IServer     (_IOContext, _Endpoint),
  m_SslContext(_SslMethod)
{
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

void SslServer::SetSslContextOptions(boost::asio::ssl::context_base::options _Options)
{
  m_SslContext.set_options(_Options);
}

void SslServer::SetSslKeysPaths(const std::string & _PrivateKeyPath,
                                const std::string & _CertificatePath)
{
  m_SslContext.use_certificate_chain_file(_CertificatePath);
  m_SslContext.use_private_key_file(_PrivateKeyPath, boost::asio::ssl::context::pem);
}