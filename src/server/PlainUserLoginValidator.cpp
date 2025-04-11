#include "PlainUserLoginValidator.hpp"
#include "IChatUser.hpp"
#include "../common/LoginData.hpp"

// --- Interface ---
void PlainUserLoginValidator::ValidateUserLogin(std::shared_ptr<IChatUser>                      _User,
                                                std::function<void(std::shared_ptr<IChatUser>)> _SuccessCallback,
                                                std::function<void(std::shared_ptr<IChatUser>)> _FailCallback)
{
  const LoginData & Data = _User->GetLoginData();

  if (0 != Data.UserID)
  {
    _SuccessCallback(_User);

    return;
  }

  _FailCallback(_User);
}
