#include "IChatUser.hpp"

// --- Constructor/Destructor ---
IChatUser::IChatUser(ChatSpace & _ChatSpace) :
  m_ChatSpace(_ChatSpace)
{
}

IChatUser::~IChatUser()
{
}

// --- Interface ---
void IChatUser::DeliverMessage(const MessagePtr _MessagePtr)
{
  const std::vector<MessageBlockPtr> VecBlocks = _MessagePtr->GetVectorOfBlocks();

  for (const MessageBlockPtr & BlockPtr : VecBlocks)
    m_MessageBlocksToWrite.push(BlockPtr);

  DoWrite();
}

void IChatUser::OnLoginSuccessful()
{
  DoReadDescriptor();
}

void IChatUser::OnLoginFailed()
{
  // Empty
}

const LoginData & IChatUser::GetLoginData() const
{
  return m_LoginData;
}

// --- Service ---
void IChatUser::OnLoginDataReceived()
{
  m_ChatSpace.UserLogin(shared_from_this());
}

void IChatUser::OnMessageBlockReceived(const MessageBlockPtr _BlockPtr)
{
  if (m_MessagesToRead.end() == m_MessagesToRead.find(_BlockPtr->GetMessageID()))
    m_MessagesToRead[_BlockPtr->GetMessageID()] = std::make_shared<Message>();

  m_MessagesToRead[_BlockPtr->GetMessageID()]->AddBlock(_BlockPtr);

  if (m_MessagesToRead[_BlockPtr->GetMessageID()]->HasAllBlocks())
    CheckReadyMessagesToRead();
}

void IChatUser::OnMessageReceived(const MessagePtr _MessagePtr)
{
  m_ChatSpace.DeliverMessage(_MessagePtr);
}

void IChatUser::CheckReadyMessagesToRead()
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