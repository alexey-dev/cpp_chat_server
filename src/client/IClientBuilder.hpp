#ifndef ICLIENT_BUILDER_HPP
#define ICLIENT_BUILDER_HPP

#include <boost/asio.hpp>
#include "IClient.hpp"
#include "InputArguments.hpp"

class IClientBuilder
{
  public: // --- Constructor/Destructor ---
    IClientBuilder(const InputArguments &    _Arguments,
                   boost::asio::io_context & _IOContext);

    ~IClientBuilder();

  public: // --- Interface ---
    std::shared_ptr<IClient> GetProduct();

    virtual void InitClientSetup() = 0;

    virtual void InitSpecificSettings() = 0;

  protected: // --- Service ---
    const LoginData GetLoginData() const;

  protected: // --- Member variables ---
    std::shared_ptr<IClient>  m_Client;
    const InputArguments &    m_Arguments;
    boost::asio::io_context & m_IOContext;
};

#endif // ICLIENT_BUILDER_HPP