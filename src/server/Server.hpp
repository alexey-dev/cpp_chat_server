#ifndef SERVER_HPP
#define SERVER_HPP

#include <boost/asio.hpp>
#include "ChatSpace.hpp"

class Server
{
  public: // --- Constructor ---
    Server(boost::asio::io_context &              _IOContext,
           const boost::asio::ip::tcp::endpoint & _Endpoint);

  private: // Service
    void DoAccept();

  private: // --- Member variables ---
    boost::asio::ip::tcp::acceptor m_Acceptor;
    ChatSpace                      m_ChatSpace;
};

#endif // SERVER_HPP