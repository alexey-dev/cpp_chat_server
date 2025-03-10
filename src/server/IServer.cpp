#include "IServer.hpp"

// --- Constructor/Destructor ---
IServer::IServer(boost::asio::io_context &              _IOContext,
                 const boost::asio::ip::tcp::endpoint & _Endpoint) :
  m_Acceptor(_IOContext, _Endpoint)
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
