#include "ChatSpace.hpp"
#include "ChatUser.hpp"

// --- Interface ---
void ChatSpace::JoinUser(std::shared_ptr<ChatUser> _User)
{
  std::cout << "User joined" << std::endl;

  m_Users.insert(_User);
}

void ChatSpace::LeaveUser(std::shared_ptr<ChatUser> _User)
{
  std::cout << "User left" << std::endl;

  m_Users.erase(_User);
}

void ChatSpace::DeliverMessage(const MessagePtr _MessagePtr)
{
  std::cout << "Message:" << _MessagePtr->GetBody() << std::endl;

  for (const std::shared_ptr<ChatUser> & User : m_Users)
    User->DeliverMessage(_MessagePtr);
}