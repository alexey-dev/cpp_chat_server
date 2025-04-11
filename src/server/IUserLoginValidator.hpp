#ifndef IUSER_LOGIN_VALIDATOR_HPP
#define IUSER_LOGIN_VALIDATOR_HPP

#include <functional>
#include <memory>

class IChatUser;

class IUserLoginValidator
{
  public: // --- Destructor ---
    virtual ~IUserLoginValidator();

  public: // --- Interface ---
    virtual void ValidateUserLogin(std::shared_ptr<IChatUser>                      _User,
                                   std::function<void(std::shared_ptr<IChatUser>)> _SuccessCallback,
                                   std::function<void(std::shared_ptr<IChatUser>)> _FailCallback) = 0;
};

#endif // IUSER_LOGIN_VALIDATOR_HPP