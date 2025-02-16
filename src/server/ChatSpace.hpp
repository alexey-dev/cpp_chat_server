#ifndef CHAT_SPACE_HPP
#define CHAT_SPACE_HPP

#include <set>
#include <memory>
#include "../common/Message.hpp"

class ChatUser;

class ChatSpace
{
  public: // --- Interface ---
    void JoinUser(std::shared_ptr<ChatUser> _User);

    void LeaveUser(std::shared_ptr<ChatUser> _User);

    void DeliverMessage(const MessagePtr _MessagePtr);

  private: // --- Member variables ---
    std::set<std::shared_ptr<ChatUser>> m_Users;
};

#endif // CHAT_SPACE_HPP