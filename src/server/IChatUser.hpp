#ifndef ICHAT_USER_HPP
#define ICHAT_USER_HPP

#include <memory>
#include <queue>
#include <map>
#include <boost/asio.hpp>
#include "../common/Message.hpp"
#include "../common/LoginData.hpp"
#include "ChatSpace.hpp"

class IChatUser : public std::enable_shared_from_this<IChatUser>
{
  public: // --- Constructor/Destructor ---
    IChatUser(ChatSpace & _ChatSpace);

    virtual ~IChatUser();

  public: // --- Interface ---
    virtual void Start() = 0;

    void DeliverMessage(const MessagePtr _Message);

    void OnLoginSuccessful();

    void OnLoginFailed();

    const LoginData & GetLoginData() const;

  protected: // --- Service ---
    virtual void DoReadLogin() = 0;

    virtual void DoReadDescriptor() = 0;

    virtual void DoReadBody() = 0;

    virtual void DoWrite() = 0;

    void OnLoginDataReceived();

    void OnMessageBlockReceived(const MessageBlockPtr _BlockPtr);

    void OnMessageReceived(const MessagePtr _MessagePtr);

    void CheckReadyMessagesToRead();

  protected: // --- Member variables ---
    std::queue<MessageBlockPtr>   m_MessageBlocksToWrite;
    std::map<int32_t, MessagePtr> m_MessagesToRead;
    MessageBlockPtr               m_ReadMessageBlockPtr;
    MessageBlockDescriptor        m_ReadDescriptor;
    LoginData                     m_LoginData;
    ChatSpace &                   m_ChatSpace;
};

#endif // ICHAT_USER_HPP