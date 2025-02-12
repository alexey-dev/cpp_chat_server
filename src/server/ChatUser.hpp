#ifndef CHAT_USER_HPP
#define CHAT_USER_HPP

#include <memory>
#include <deque>
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

    void DeliverMessage(const Message & _Message);

  private: // --- Service ---
    void DoRead();

    void DoWrite();

    void OnMessageReceived(const Message & _Message);

  private: // --- Member variables ---
    boost::asio::ip::tcp::socket m_Socket;
    std::deque<Message>          m_Messages;
    Message                      m_ReadMessage;
    ChatSpace &                  m_ChatSpace;
};

#endif // CHAT_USER_HPP