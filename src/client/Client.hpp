#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include <boost/asio.hpp>
#include "../common/Message.hpp"
#include "../common/MessageBuilder.hpp"
#include "../common/MessageBlock.hpp"
#include <queue>
#include <map>

class Client
{
  public: // --- Constructor ---
    Client(boost::asio::io_context &                            _IOContext,
           const boost::asio::ip::tcp::resolver::results_type & _Endpoints);

  public: // --- Interface ---
    void Write(const MessageBlockPtr & _Message);

    void WriteText(char * _Message);

    void Close();

  private: // --- Service ---
    void DoConnect(const boost::asio::ip::tcp::resolver::results_type & _Endpoints);

    void DoWrite();

    void PostWrite();

    void DoReadDescriptor();

    void DoReadBody();

    void OnMessageBlockReceived(const MessageBlockPtr _BlockPtr);

    void OnMessageReceived(const MessagePtr _MessagePtr);

    void CheckReadyMessagesToRead();

  private: // --- Member variables ---
    boost::asio::io_context&     m_IOContext;
    boost::asio::ip::tcp::socket m_Socket;
    MessageBuilder               m_MessageBuilder;
    std::queue<MessageBlockPtr>  m_MessagesToWrite;
    std::map<int32_t, MessagePtr>      m_MessagesToRead;
    MessageBlockPtr                    m_ReadMessageBlockPtr;
    MessageBlockDescriptor             m_ReadDescriptor;
};

#endif // CLIENT_HPP