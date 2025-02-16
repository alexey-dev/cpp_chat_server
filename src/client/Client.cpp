#include "Client.hpp"
#include <vector>

// --- Constructor ---
Client::Client(boost::asio::io_context &                            _IOContext,
               const boost::asio::ip::tcp::resolver::results_type & _Endpoints) :
  m_IOContext(_IOContext),
  m_Socket   (_IOContext)
{
  DoConnect(_Endpoints);
}

// --- Interface ---
void Client::Write(const MessageBlockPtr & _Message)
{
  m_MessagesToWrite.push(_Message);

  PostWrite();
}

void Client::WriteText(char * _Message)
{
  const std::vector<MessageBlockPtr> Blocks = m_MessageBuilder.CreateBlocksFromRawMessage(_Message);

  for (const MessageBlockPtr & Ptr : Blocks)
    m_MessagesToWrite.push(Ptr);

  PostWrite();
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

      DoReadDescriptor();
    });
}

void Client::DoWrite()
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

void Client::PostWrite()
{
  if (m_MessagesToWrite.empty())
    return;

  boost::asio::post(m_IOContext,
    [this]()
    {
      DoWrite();
    });
}
void Client::DoReadDescriptor()
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

void Client::DoReadBody()
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

void Client::OnMessageBlockReceived(const MessageBlockPtr _BlockPtr)
{
  if (m_MessagesToRead.end() == m_MessagesToRead.find(_BlockPtr->GetMessageID()))
    m_MessagesToRead[_BlockPtr->GetMessageID()] = std::make_shared<Message>();

  m_MessagesToRead[_BlockPtr->GetMessageID()]->AddBlock(_BlockPtr);

  if (m_MessagesToRead[_BlockPtr->GetMessageID()]->HasAllBlocks())
    CheckReadyMessagesToRead();
}

void Client::OnMessageReceived(const MessagePtr _MessagePtr)
{
  std::cout << "Received: " << _MessagePtr->GetBody() << std::endl;
}

void Client::CheckReadyMessagesToRead()
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