#ifndef ICLIENT_HPP
#define ICLIENT_HPP

#include <queue>
#include <map>
#include <boost/asio.hpp>
#include "../common/LoginData.hpp"
#include "../common/Message.hpp"
#include "../common/MessageBuilder.hpp"
#include "../common/MessageBlock.hpp"

class IClient
{
  public: // --- Constructor/Destructor ---
    IClient(boost::asio::io_context &                            _IOContext,
            const boost::asio::ip::tcp::resolver::results_type & _Endpoints,
            const LoginData &                                    _LoginData);

    virtual ~IClient();

  public: // --- Interface ---
    void Write(const MessageBlockPtr & _Message);

    void WriteText(char * _Message);

    void Start();

    virtual void Close() = 0;

  protected: // --- Service ---
    virtual void DoConnect(const boost::asio::ip::tcp::resolver::results_type & _Endpoints) = 0;

    virtual void DoLogin() = 0;

    virtual void DoWrite() = 0;

    virtual void PostWrite() = 0;

    virtual void DoReadDescriptor() = 0;

    virtual void DoReadBody() = 0;

    void OnMessageBlockReceived(const MessageBlockPtr _BlockPtr);

    void OnMessageReceived(const MessagePtr _MessagePtr);

    void CheckReadyMessagesToRead();

  protected: // --- Member variables ---
    boost::asio::io_context &                          m_IOContext;
    const boost::asio::ip::tcp::resolver::results_type m_Endpoints;
    MessageBuilder                                     m_MessageBuilder;
    std::queue<MessageBlockPtr>                        m_MessagesToWrite;
    std::map<int32_t, MessagePtr>                      m_MessagesToRead;
    MessageBlockPtr                                    m_ReadMessageBlockPtr;
    MessageBlockDescriptor                             m_ReadDescriptor;
    LoginData                                          m_LoginData;
};

#endif // ICLIENT_HPP