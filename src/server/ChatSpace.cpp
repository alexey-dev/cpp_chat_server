#include "ChatSpace.hpp"
#include "IChatUser.hpp"

// --- Constructor ---
ChatSpace::ChatSpace(std::shared_ptr<IUserLoginValidator> _Validator) :
  m_UserLoginValidator(_Validator)
{
  // Empty
}

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
  auto SuccessCallback = std::bind(&ChatSpace::LoginValidationSucceded, *this, std::placeholders::_1);
  auto FailCallback    = std::bind(&ChatSpace::LoginValidationFailed, *this, std::placeholders::_1);

  m_UserLoginValidator->ValidateUserLogin(_User, SuccessCallback, FailCallback);
}

void ChatSpace::DeliverMessage(const MessagePtr _MessagePtr)
{
  std::cout << "Message:" << _MessagePtr->GetBody() << std::endl;

  for (const std::shared_ptr<IChatUser> & User : m_Users)
    User->DeliverMessage(_MessagePtr);
}

// --- Sevice ---
void ChatSpace::LoginValidationSucceded(std::shared_ptr<IChatUser> _User)
{
  _User->OnLoginSuccessful();
  std::cout << "User "<< _User->GetLoginData().UserID << " successfully logged in" << std::endl;
}

void ChatSpace::LoginValidationFailed(std::shared_ptr<IChatUser> _User)
{
  std::cout << "User "<< _User->GetLoginData().UserID << " failed to log in" << std::endl;
  LeaveUser(_User);
}
