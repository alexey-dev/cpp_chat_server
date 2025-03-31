#include "SslClientBuilder.hpp"
#include "SslClient.hpp"

// --- Constructor/Destructor ---
SslClientBuilder::SslClientBuilder(const InputArguments &     _Arguments,
                                   boost::asio::io_context &  _IOContext) :
  IClientBuilder(_Arguments, _IOContext),
  m_SslContext  (boost::asio::ssl::context::sslv23)
{
}

// --- Interface ---
void SslClientBuilder::InitClientSetup()
{
  boost::asio::ip::tcp::resolver               Resolver(m_IOContext);
  boost::asio::ip::tcp::resolver::results_type Endpoints = Resolver.resolve(m_Arguments.Host, std::to_string(m_Arguments.Port));

  m_Client = std::make_shared<SslClient>(m_IOContext, m_SslContext, Endpoints, GetLoginData());
}

void SslClientBuilder::InitSpecificSettings()
{
  m_SslContext.load_verify_file(m_Arguments.CertificateSSLPath);
}