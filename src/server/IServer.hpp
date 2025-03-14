#ifndef ISERVER_HPP
#define ISERVER_HPP

#include <boost/asio.hpp>
#include "ChatSpace.hpp"

class IServer
{
  public: // --- Constructor/Destructor ---
    IServer(boost::asio::io_context &              _IOContext,
            const boost::asio::ip::tcp::endpoint & _Endpoint);

    virtual ~IServer();

  public: // --- Interface ---
    void Start();

  protected: // --- Service ---
    virtual void DoAccept() = 0;

  protected: // --- Member variables ---
    boost::asio::ip::tcp::acceptor m_Acceptor;
    ChatSpace                      m_ChatSpace;
};

#endif // ISERVER_HPP