#include "SslClient.hpp"
#include <vector>

// --- Constructor ---
SslClient::SslClient(boost::asio::io_context &                            _IOContext,
                     boost::asio::ssl::context &                          _SslContext,
                     const boost::asio::ip::tcp::resolver::results_type & _Endpoints) :
  IClient  (_IOContext, _Endpoints),
  m_Socket (_IOContext, _SslContext)
{
  m_Socket.set_verify_mode(boost::asio::ssl::verify_peer);
  m_Socket.set_verify_callback(std::bind(&SslClient::VerifyCertificateCallback, this, std::placeholders::_1, std::placeholders::_2));
}

// --- Interface ---
void SslClient::Close()
{
  boost::asio::post(m_IOContext,
    [this]()
    {
      m_Socket.lowest_layer().close(); 
    });
}

// --- Service ---
bool SslClient::VerifyCertificateCallback(bool                               _IsPreverified,
                                          boost::asio::ssl::verify_context & _Context)
{
  constexpr uint16_t SUBJECT_LENGTH = 256;
  char               SubjectName[SUBJECT_LENGTH];
  X509 *             Certificate    = X509_STORE_CTX_get_current_cert(_Context.native_handle());

  X509_NAME_oneline(X509_get_subject_name(Certificate), SubjectName, SUBJECT_LENGTH);

  std::cout << "Verifying " << SubjectName << std::endl;

  return _IsPreverified;
}

void SslClient::DoHandshake()
{
  m_Socket.async_handshake(boost::asio::ssl::stream_base::client,
    [this](const boost::system::error_code & _Error)
    {
      if (_Error)
      {
        std::cout << "Handshake failed: " << _Error.message() << std::endl;
      }

      DoReadDescriptor();
    });
}

void SslClient::DoConnect(const boost::asio::ip::tcp::resolver::results_type & _Endpoints)
{
  boost::asio::async_connect(m_Socket.lowest_layer(), _Endpoints,
    [this](boost::system::error_code _ErrorCode, boost::asio::ip::tcp::endpoint _EndpointsInternal)
    {
      if (_ErrorCode)
        return;

      DoHandshake();
    });
}

void SslClient::DoWrite()
{
  boost::asio::async_write(m_Socket,
    boost::asio::buffer(m_MessagesToWrite.front()->GetStartDataAddress(),
                        m_MessagesToWrite.front()->GetDataSize()),
      [this](boost::system::error_code _ErrorCode, std::size_t _Length)
      {
        if (_ErrorCode)
        {
          Close();
          return;
        }

        m_MessagesToWrite.pop();

        if (!m_MessagesToWrite.empty())
          PostWrite();
      });
}

void SslClient::PostWrite()
{
  if (m_MessagesToWrite.empty())
    return;

  boost::asio::post(m_IOContext,
    [this]()
    {
      DoWrite();
    });
}
void SslClient::DoReadDescriptor()
{
  boost::asio::async_read(m_Socket, boost::asio::buffer(std::addressof(m_ReadDescriptor), MessageBlock::DESCRIPTOR_SIZE),
    [this](boost::system::error_code _ErrorCode, std::size_t _Length)
    {
      if (_ErrorCode)
      {
        Close();
        return;
      }

      DoReadBody();
    });
}

void SslClient::DoReadBody()
{
  m_ReadMessageBlockPtr = std::make_shared<MessageBlock>(m_ReadDescriptor);

  boost::asio::async_read(m_Socket, boost::asio::buffer(m_ReadMessageBlockPtr->GetBody(), m_ReadDescriptor.BodySize),
    [this](boost::system::error_code _ErrorCode, std::size_t _Length)
    {
      if (_ErrorCode)
      {
        Close();
        return;
      }

      OnMessageBlockReceived(m_ReadMessageBlockPtr);
      DoReadDescriptor();
    });
}