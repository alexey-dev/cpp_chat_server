#include "IServer.hpp"
#include "PlainUserLoginValidator.hpp"

// --- Constructor/Destructor ---
IServer::IServer(boost::asio::io_context &              _IOContext,
                 const boost::asio::ip::tcp::endpoint & _Endpoint) :
  m_Acceptor(_IOContext, _Endpoint),
  m_ChatSpace(std::make_shared<PlainUserLoginValidator>())
{
}

IServer::~IServer()
{
}

// --- Interface ---
void IServer::Start()
{
  DoAccept();
}
