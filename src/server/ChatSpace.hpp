#ifndef CHAT_SPACE_HPP
#define CHAT_SPACE_HPP

#include <set>
#include <memory>
#include "../common/Message.hpp"

class IChatUser;

class ChatSpace
{
  public: // --- Interface ---
    void JoinUser(std::shared_ptr<IChatUser> _User);

    void LeaveUser(std::shared_ptr<IChatUser> _User);

    void UserLogin(std::shared_ptr<IChatUser> _User);

    void DeliverMessage(const MessagePtr _MessagePtr);

  private: // --- Sevice ---
    bool IsUserLoginValid(std::shared_ptr<IChatUser> _User) const;

  private: // --- Member variables ---
    std::set<std::shared_ptr<IChatUser>> m_Users;
};

#endif // CHAT_SPACE_HPP