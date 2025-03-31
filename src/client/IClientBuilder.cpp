#include "IClientBuilder.hpp"

// --- Constructor/Destructor ---
IClientBuilder::IClientBuilder(const InputArguments &    _Arguments,
                               boost::asio::io_context & _IOContext) :
  m_Arguments(_Arguments),
  m_IOContext(_IOContext)
{
}

IClientBuilder::~IClientBuilder()
{
}

// --- Interface ---
std::shared_ptr<IClient> IClientBuilder::GetProduct()
{
  return m_Client;
}

// --- Service ---
const LoginData IClientBuilder::GetLoginData() const
{
  return {m_Arguments.UserID};
}