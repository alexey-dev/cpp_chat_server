#ifndef PLAIN_SERVER_HPP
#define PLAIN_SERVER_HPP

#include <boost/asio.hpp>
#include "IServer.hpp"

class PlainServer : public IServer
{
  public: // --- Constructor ---
    PlainServer(boost::asio::io_context &              _IOContext,
                const boost::asio::ip::tcp::endpoint & _Endpoint);

  private: // --- Service ---
    void DoAccept() override;
};

#endif // PLAIN_SERVER_HPP