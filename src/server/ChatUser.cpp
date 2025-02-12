#include "ChatUser.hpp"

// --- Constructor ---
ChatUser::ChatUser(boost::asio::ip::tcp::socket _Socket,
                   ChatSpace & _ChatSpace) :
  m_Socket   (std::move(_Socket)),
  m_ChatSpace(_ChatSpace)
{
}

// --- Interface ---
void ChatUser::Start()
{
  DoRead();
}

void ChatUser::DeliverMessage(const Message & _Message)
{
  m_Messages.push_back(_Message);
  DoWrite();
}

// --- Service ---
void ChatUser::DoRead()
{
  std::shared_ptr<ChatUser> SelfCounter(shared_from_this());

  boost::asio::async_read(m_Socket, boost::asio::buffer(m_ReadMessage.GetBody(), Message::MAX_BODY_SIZE),
      [this, SelfCounter](boost::system::error_code _ErrorCode, std::size_t _Length)
      {
        if (_ErrorCode)
        {
          m_ChatSpace.LeaveUser(shared_from_this());
          return;
        }

        OnMessageReceived(m_ReadMessage);
        DoRead();
      });
}

void ChatUser::DoWrite()
{
  std::shared_ptr<ChatUser> SelfCounter(shared_from_this());

  boost::asio::async_write(m_Socket, boost::asio::buffer(m_Messages.front().GetBody(), Message::MAX_BODY_SIZE),
    [this, SelfCounter](boost::system::error_code _ErrorCode, std::size_t _Length)
    {
      if (_ErrorCode)
      {
        m_ChatSpace.LeaveUser(shared_from_this());
        return;
      }

      m_Messages.pop_front();

      if (m_Messages.empty())
        return;

      DoWrite();
    });
}

void ChatUser::OnMessageReceived(const Message & _Message)
{
  m_ChatSpace.DeliverMessage(_Message);
}
