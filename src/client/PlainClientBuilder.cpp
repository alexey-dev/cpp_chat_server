#include "PlainClientBuilder.hpp"
#include "PlainClient.hpp"

// --- Constructor/Destructor ---
PlainClientBuilder::PlainClientBuilder(const InputArguments &    _Arguments,
                                       boost::asio::io_context & _IOContext) :
  IClientBuilder(_Arguments, _IOContext)
{
}

// --- Interface ---
void PlainClientBuilder::InitClientSetup()
{
  boost::asio::ip::tcp::resolver               Resolver(m_IOContext);
  boost::asio::ip::tcp::resolver::results_type Endpoints = Resolver.resolve(m_Arguments.Host, std::to_string(m_Arguments.Port));

  m_Client = std::make_shared<PlainClient>(m_IOContext, Endpoints);
}

void PlainClientBuilder::InitSpecificSettings()
{
  // Empty
}