#ifndef CHAT_USER_HPP
#define CHAT_USER_HPP

#include <memory>
#include <queue>
#include <map>
#include <boost/asio.hpp>
#include "../common/Message.hpp"
#include "ChatSpace.hpp"

class ChatUser : public std::enable_shared_from_this<ChatUser>
{
  public: // --- Constructor ---
    ChatUser(boost::asio::ip::tcp::socket _Socket,
             ChatSpace & _ChatSpace);

  public: // --- Interface ---
    void Start();

    void DeliverMessage(const MessagePtr _Message);

  private: // --- Service ---
    void DoReadDescriptor();

    void DoReadBody();

    void DoWrite();

    void OnMessageBlockReceived(const MessageBlockPtr _BlockPtr);

    void OnMessageReceived(const MessagePtr _MessagePtr);

    void CheckReadyMessagesToRead();

  private: // --- Member variables ---
    boost::asio::ip::tcp::socket  m_Socket;
    std::queue<MessageBlockPtr>   m_MessageBlocksToWrite;
    std::map<int32_t, MessagePtr> m_MessagesToRead;
    MessageBlockPtr               m_ReadMessageBlockPtr;
    MessageBlockDescriptor        m_ReadDescriptor;
    ChatSpace &                   m_ChatSpace;
};

#endif // CHAT_USER_HPP