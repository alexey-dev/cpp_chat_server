#include "PlainServer.hpp"
#include "ChatUser.hpp"

// --- Constructor ---
PlainServer::PlainServer(boost::asio::io_context &              _IOContext,
                         const boost::asio::ip::tcp::endpoint & _Endpoint) :
  IServer(_IOContext, _Endpoint)
{
  DoAccept();
}

// --- Service ---
void PlainServer::DoAccept()
{
  m_Acceptor.async_accept(
    [this](boost::system::error_code _ErrorCode,
           boost::asio::ip::tcp::socket _Socket)
    {
      if (!_ErrorCode)
      {
        std::shared_ptr<ChatUser> User = std::make_shared<ChatUser>(std::move(_Socket), m_ChatSpace);

        m_ChatSpace.JoinUser(User);
        User->Start();
      }

      DoAccept();
    });
}