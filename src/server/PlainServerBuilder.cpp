#include "PlainServerBuilder.hpp"
#include "PlainServer.hpp"

// --- Constructor/Destructor ---
PlainServerBuilder::PlainServerBuilder(const InputArguments &    _Arguments,
                                       boost::asio::io_context & _IOContext) :
  IServerBuilder(_Arguments, _IOContext)
{
}

// --- Interface ---
void PlainServerBuilder::InitServerSetup()
{
  boost::asio::ip::tcp::endpoint Endpoint(boost::asio::ip::tcp::v4(), m_Arguments.Port);
  m_Server = std::make_shared<PlainServer>(m_IOContext, Endpoint);
}

void PlainServerBuilder::InitSpecificSettings()
{
  // Empty
}