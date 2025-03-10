#ifndef SSL_CHAT_USER_HPP
#define SSL_CHAT_USER_HPP

#include <memory>
#include <queue>
#include <map>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include "../common/Message.hpp"
#include "IChatUser.hpp"
#include "ChatSpace.hpp"

class SslChatUser : public IChatUser, public std::enable_shared_from_this<SslChatUser>
{
  public: // --- Constructor ---
    SslChatUser(boost::asio::ssl::stream<boost::asio::ip::tcp::socket> _Socket,
                ChatSpace &                                            _ChatSpace);

  public: // --- Interface ---
    void Start() override;

  private: // --- Service ---
    void DoHandshake();

    void DoReadDescriptor() override;

    void DoReadBody() override;

    void DoWrite() override;

  private: // --- Member variables ---
    boost::asio::ssl::stream<boost::asio::ip::tcp::socket>  m_Socket;
};

#endif // SSL_CHAT_USER_HPP