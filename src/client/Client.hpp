#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include <boost/asio.hpp>
#include "../common/Message.hpp"
#include <vector>

class Client
{
  public: // --- Constructor ---
    Client(boost::asio::io_context &                            _IOContext,
           const boost::asio::ip::tcp::resolver::results_type & _Endpoints);

  public: // --- Interface ---
    void Write(const Message & _Message);

    void Close();

  private: // --- Service ---
    void DoConnect(const boost::asio::ip::tcp::resolver::results_type & _Endpoints);

    void DoRead();

    void DoWrite();

  private: // --- Member variables ---
    boost::asio::io_context&     m_IOContext;
    boost::asio::ip::tcp::socket m_Socket;
    std::vector<Message>         m_Messages;
    Message                      m_ReadMessages;
};

#endif // CLIENT_HPP