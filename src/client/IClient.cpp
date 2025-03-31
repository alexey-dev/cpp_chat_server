#include "IClient.hpp"
#include <vector>

// --- Constructor/Destructor ---
IClient::IClient(boost::asio::io_context &                            _IOContext,
                 const boost::asio::ip::tcp::resolver::results_type & _Endpoints,
                 const LoginData &                                    _LoginData) :
  m_IOContext(_IOContext),
  m_Endpoints(_Endpoints),
  m_LoginData(_LoginData)
{
}

IClient::~IClient()
{
}

// --- Interface ---
void IClient::Write(const MessageBlockPtr & _Message)
{
  m_MessagesToWrite.push(_Message);

  PostWrite();
}

void IClient::WriteText(char * _Message)
{
  const std::vector<MessageBlockPtr> Blocks = m_MessageBuilder.CreateBlocksFromRawMessage(_Message);

  for (const MessageBlockPtr & Ptr : Blocks)
    m_MessagesToWrite.push(Ptr);

  PostWrite();
}

void IClient::Start()
{
  DoConnect(m_Endpoints);
}

// --- Service ---
void IClient::OnMessageBlockReceived(const MessageBlockPtr _BlockPtr)
{
  if (m_MessagesToRead.end() == m_MessagesToRead.find(_BlockPtr->GetMessageID()))
    m_MessagesToRead[_BlockPtr->GetMessageID()] = std::make_shared<Message>();

  m_MessagesToRead[_BlockPtr->GetMessageID()]->AddBlock(_BlockPtr);

  if (m_MessagesToRead[_BlockPtr->GetMessageID()]->HasAllBlocks())
    CheckReadyMessagesToRead();
}

void IClient::OnMessageReceived(const MessagePtr _MessagePtr)
{
  std::cout << "Received: " << _MessagePtr->GetBody() << std::endl;
}

void IClient::CheckReadyMessagesToRead()
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