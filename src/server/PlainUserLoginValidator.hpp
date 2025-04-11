#ifndef PLAIN_USER_LOGIN_VALIDATOR_HPP
#define PLAIN_USER_LOGIN_VALIDATOR_HPP

#include "IUserLoginValidator.hpp"

class PlainUserLoginValidator : public IUserLoginValidator
{
  public: // --- Interface ---
    void ValidateUserLogin(std::shared_ptr<IChatUser>                      _User,
                                   std::function<void(std::shared_ptr<IChatUser>)> _SuccessCallback,
                                   std::function<void(std::shared_ptr<IChatUser>)> _FailCallback) override;
};

#endif // PLAIN_USER_LOGIN_VALIDATOR_HPP