#include "Client.hpp"

// --- Constructor ---
Client::Client(boost::asio::io_context &                            _IOContext,
               const boost::asio::ip::tcp::resolver::results_type & _Endpoints) :
  m_IOContext(_IOContext),
  m_Socket   (_IOContext)
{
  DoConnect(_Endpoints);
}

// --- Interface ---
void Client::Write(const Message & _Message)
{
  boost::asio::post(m_IOContext,
    [this, _Message]()
    {
      m_Messages.push_back(_Message);
      DoWrite();
    });
}

void Client::Close()
{
  boost::asio::post(m_IOContext, [this]()
    {
      m_Socket.close(); 
    });
}

// --- Service ---
void Client::DoConnect(const boost::asio::ip::tcp::resolver::results_type & _Endpoints)
{
  boost::asio::async_connect(m_Socket, _Endpoints,
    [this](boost::system::error_code _ErrorCode, boost::asio::ip::tcp::endpoint _EndpointsInternal)
    {
      if (_ErrorCode)
        return;

      DoRead();
    });
}

void Client::DoRead()
{
  boost::asio::async_read(m_Socket, boost::asio::buffer(m_ReadMessages.GetBody(), Message::MAX_BODY_SIZE),
    [this](boost::system::error_code _ErrorCode, std::size_t _Lenght)
    {
      if (_ErrorCode)
      {
        Close();
        return;
      }

      std::cout << "Received: " << m_ReadMessages.GetBody() << std::endl;
      DoRead();
    });
}

void Client::DoWrite()
{
  boost::asio::async_write(m_Socket,
    boost::asio::buffer(m_Messages.back().GetBody(),
                        Message::MAX_BODY_SIZE),
                        [this](boost::system::error_code _ErrorCode, std::size_t _Length)
    {
      if (_ErrorCode)
      {
        Close();
        return;
      }
    });
}