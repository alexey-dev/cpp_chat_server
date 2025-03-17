#include "SslServerBuilder.hpp"
#include "SslServer.hpp"

// --- Constructor/Destructor ---
SslServerBuilder::SslServerBuilder(const InputArguments &    _Arguments,
                                   boost::asio::io_context & _IOContext) :
  IServerBuilder(_Arguments, _IOContext)
{
}

// --- Interface ---
void SslServerBuilder::InitServerSetup()
{
  boost::asio::ip::tcp::endpoint Endpoint(boost::asio::ip::tcp::v4(), m_Arguments.Port);
  m_Server = std::make_shared<SslServer>(m_IOContext, boost::asio::ssl::context::sslv23, Endpoint);
}

void SslServerBuilder::InitSpecificSettings()
{
  std::shared_ptr<SslServer> Server = std::dynamic_pointer_cast<SslServer>(m_Server);

  assert(nullptr != Server);

  Server->SetSslContextOptions(boost::asio::ssl::context::default_workarounds | boost::asio::ssl::context::no_sslv2);
  Server->SetSslKeysPaths(m_Arguments.PrivateKeySSLPath, m_Arguments.CertificateSSLPath);
}