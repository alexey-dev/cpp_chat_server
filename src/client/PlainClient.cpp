#include "PlainClient.hpp"

// --- Constructor ---
PlainClient::PlainClient(boost::asio::io_context &                            _IOContext,
                         const boost::asio::ip::tcp::resolver::results_type & _Endpoints,
                         const LoginData &                                    _LoginData) :
  IClient  (_IOContext, _Endpoints, _LoginData),
  m_Socket (_IOContext)
{
}

// --- Interface ---
void PlainClient::Close()
{
  boost::asio::post(m_IOContext, [this]()
    {
      m_Socket.close(); 
    });
}

// --- Service ---
void PlainClient::DoConnect(const boost::asio::ip::tcp::resolver::results_type & _Endpoints)
{
  boost::asio::async_connect(m_Socket, _Endpoints,
    [this](boost::system::error_code _ErrorCode, boost::asio::ip::tcp::endpoint _EndpointsInternal)
    {
      if (_ErrorCode)
        return;

      DoLogin();
    });
}

void PlainClient::DoLogin()
{
  boost::asio::async_write(m_Socket,
    boost::asio::buffer(std::addressof(m_LoginData),
                        sizeof(LoginData)),
      [this](boost::system::error_code _ErrorCode, std::size_t _Length)
      {
        if (_ErrorCode)
        {
          Close();
          return;
        }

        DoReadDescriptor();
      });
}

void PlainClient::DoWrite()
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

void PlainClient::PostWrite()
{
  if (m_MessagesToWrite.empty())
    return;

  boost::asio::post(m_IOContext,
    [this]()
    {
      DoWrite();
    });
}
void PlainClient::DoReadDescriptor()
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

void PlainClient::DoReadBody()
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