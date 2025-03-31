#include "ChatSpace.hpp"
#include "IChatUser.hpp"

// --- Interface ---
void ChatSpace::JoinUser(std::shared_ptr<IChatUser> _User)
{
  std::cout << "User joined" << std::endl;

  m_Users.insert(_User);
}

void ChatSpace::LeaveUser(std::shared_ptr<IChatUser> _User)
{
  std::cout << "User left" << std::endl;

  m_Users.erase(_User);
}

void ChatSpace::UserLogin(std::shared_ptr<IChatUser> _User)
{
  if (!IsUserLoginValid(_User))
  {
    LeaveUser(_User);

    return;
  }

  std::cout << "User successfully logged in" << std::endl;

  _User->OnLoginSuccessful();
}

void ChatSpace::DeliverMessage(const MessagePtr _MessagePtr)
{
  std::cout << "Message:" << _MessagePtr->GetBody() << std::endl;

  for (const std::shared_ptr<IChatUser> & User : m_Users)
    User->DeliverMessage(_MessagePtr);
}

// --- Sevice ---
bool ChatSpace::IsUserLoginValid(std::shared_ptr<IChatUser> _User) const
{
  const LoginData & Data = _User->GetLoginData();

  // TODO: Check login validation later

  return true;
}
