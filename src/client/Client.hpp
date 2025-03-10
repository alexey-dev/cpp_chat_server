#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include <boost/asio.hpp>
#include "IClient.hpp"
#include "../common/Message.hpp"
#include "../common/MessageBuilder.hpp"
#include "../common/MessageBlock.hpp"
#include <queue>
#include <map>

class Client : public IClient
{
  public: // --- Constructor ---
    Client(boost::asio::io_context &                            _IOContext,
           const boost::asio::ip::tcp::resolver::results_type & _Endpoints);

  public: // --- Interface ---
    void Close() override;

  private: // --- Service ---
    void DoConnect(const boost::asio::ip::tcp::resolver::results_type & _Endpoints) override;

    void DoWrite() override;

    void PostWrite() override;

    void DoReadDescriptor() override;

    void DoReadBody() override;

  private: // --- Member variables ---
    boost::asio::ip::tcp::socket m_Socket;
};

#endif // CLIENT_HPP