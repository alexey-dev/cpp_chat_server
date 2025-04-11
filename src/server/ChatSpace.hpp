#ifndef CHAT_SPACE_HPP
#define CHAT_SPACE_HPP

#include <set>
#include <memory>
#include "../common/Message.hpp"
#include "IUserLoginValidator.hpp"

class IChatUser;

class ChatSpace
{
  public: // --- Constructor ---
    ChatSpace(std::shared_ptr<IUserLoginValidator> _Validator);

  public: // --- Interface ---
    void JoinUser(std::shared_ptr<IChatUser> _User);

    void LeaveUser(std::shared_ptr<IChatUser> _User);

    void UserLogin(std::shared_ptr<IChatUser> _User);

    void DeliverMessage(const MessagePtr _MessagePtr);

  private: // --- Sevice ---
    void LoginValidationSucceded(std::shared_ptr<IChatUser> _User);

    void LoginValidationFailed(std::shared_ptr<IChatUser> _User);

  private: // --- Member variables ---
    std::set<std::shared_ptr<IChatUser>> m_Users;
    std::shared_ptr<IUserLoginValidator> m_UserLoginValidator;
};

#endif // CHAT_SPACE_HPP