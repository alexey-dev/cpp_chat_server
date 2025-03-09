#ifndef CHAT_USER_HPP
#define CHAT_USER_HPP

#include <memory>
#include <queue>
#include <map>
#include <boost/asio.hpp>
#include "../common/Message.hpp"
#include "IChatUser.hpp"
#include "ChatSpace.hpp"

class ChatUser : public IChatUser, public std::enable_shared_from_this<ChatUser>
{
  public: // --- Constructor ---
    ChatUser(boost::asio::ip::tcp::socket _Socket,
             ChatSpace & _ChatSpace);

  public: // --- Interface ---
    void Start() override;

  private: // --- Service ---
    void DoReadDescriptor() override;

    void DoReadBody() override;

    void DoWrite() override;

  private: // --- Member variables ---
    boost::asio::ip::tcp::socket  m_Socket;
};

#endif // CHAT_USER_HPP