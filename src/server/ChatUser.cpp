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
  DoReadDescriptor();
}

void ChatUser::DeliverMessage(const MessagePtr _MessagePtr)
{
  const std::vector<MessageBlockPtr> VecBlocks = _MessagePtr->GetVectorOfBlocks();

  for (const MessageBlockPtr & BlockPtr : VecBlocks)
    m_MessageBlocksToWrite.push(BlockPtr);

  DoWrite();
}

// --- Service ---
void ChatUser::DoReadDescriptor()
{
  std::shared_ptr<ChatUser> SelfCounter(shared_from_this());

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
  std::shared_ptr<ChatUser> SelfCounter(shared_from_this());
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
  std::shared_ptr<ChatUser> SelfCounter(shared_from_this());

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

void ChatUser::OnMessageBlockReceived(const MessageBlockPtr _BlockPtr)
{
  if (m_MessagesToRead.end() == m_MessagesToRead.find(_BlockPtr->GetMessageID()))
    m_MessagesToRead[_BlockPtr->GetMessageID()] = std::make_shared<Message>();

  m_MessagesToRead[_BlockPtr->GetMessageID()]->AddBlock(_BlockPtr);

  if (m_MessagesToRead[_BlockPtr->GetMessageID()]->HasAllBlocks())
    CheckReadyMessagesToRead();
}

void ChatUser::OnMessageReceived(const MessagePtr _MessagePtr)
{
  m_ChatSpace.DeliverMessage(_MessagePtr);
}

void ChatUser::CheckReadyMessagesToRead()
{
  for (auto It = m_MessagesToRead.cbegin(); It != m_MessagesToRead.cend();)
  {
    if (It->second->HasAllBlocks())
    {
      OnMessageReceived(It->second);
      It = m_MessagesToRead.erase(It);
    }
    else
    {
      ++It;
    }
  }
}