#include "IServerBuilder.hpp"

// --- Constructor/Destructor ---
IServerBuilder::IServerBuilder(const InputArguments &    _Arguments,
                               boost::asio::io_context & _IOContext) :
  m_Arguments(_Arguments),
  m_IOContext(_IOContext)
{
}

IServerBuilder::~IServerBuilder()
{
}

// --- Interface ---
std::shared_ptr<IServer> IServerBuilder::GetProduct()
{
  return m_Server;
}