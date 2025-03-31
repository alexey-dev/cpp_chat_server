#include "ChatUser.hpp"

// --- Constructor ---
ChatUser::ChatUser(boost::asio::ip::tcp::socket _Socket,
                   ChatSpace & _ChatSpace) :
  IChatUser(_ChatSpace),
  m_Socket (std::move(_Socket))
{
}

// --- Interface ---
void ChatUser::Start()
{
  DoReadLogin();
}

// --- Service ---
void ChatUser::DoReadLogin()
{
  std::shared_ptr<IChatUser> SelfCounter(shared_from_this());

  boost::asio::async_read(m_Socket,
                          boost::asio::buffer(std::addressof(m_LoginData), sizeof(LoginData)),
    [this, SelfCounter](boost::system::error_code _ErrorCode, std::size_t _Length)
    {
      if (_ErrorCode)
      {
        m_ChatSpace.LeaveUser(shared_from_this());
        return;
      }

      OnLoginDataReceived();
    });
}

void ChatUser::DoReadDescriptor()
{
  std::shared_ptr<IChatUser> SelfCounter(shared_from_this());

  boost::asio::async_read(m_Socket,
                          boost::asio::buffer(std::addressof(m_ReadDescriptor), MessageBlock::DESCRIPTOR_SIZE),
    [this, SelfCounter](boost::system::error_code _ErrorCode, std::size_t _Length)
    {
      if (_ErrorCode)
      {
        m_ChatSpace.LeaveUser(shared_from_this());
        return;
      }

      DoReadBody();
    });
}

void ChatUser::DoReadBody()
{
  std::shared_ptr<IChatUser> SelfCounter(shared_from_this());
  m_ReadMessageBlockPtr = std::make_shared<MessageBlock>(m_ReadDescriptor);

  boost::asio::async_read(m_Socket,
                          boost::asio::buffer(m_ReadMessageBlockPtr->GetBody(), m_ReadDescriptor.BodySize),
    [this, SelfCounter](boost::system::error_code _ErrorCode, std::size_t _Length)
    {
      if (_ErrorCode)
      {
        m_ChatSpace.LeaveUser(shared_from_this());
        return;
      }

      OnMessageBlockReceived(m_ReadMessageBlockPtr);
      DoReadDescriptor();
    });
}

void ChatUser::DoWrite()
{
  std::shared_ptr<IChatUser> SelfCounter(shared_from_this());

  boost::asio::async_write(m_Socket, boost::asio::buffer(m_MessageBlocksToWrite.front()->GetStartDataAddress(), m_MessageBlocksToWrite.front()->GetDataSize()),
    [this, SelfCounter](boost::system::error_code _ErrorCode, std::size_t _Length)
    {
      if (_ErrorCode)
      {
        m_ChatSpace.LeaveUser(shared_from_this());
        return;
      }

      m_MessageBlocksToWrite.pop();

      if (m_MessageBlocksToWrite.empty())
        return;

      DoWrite();
    });
}