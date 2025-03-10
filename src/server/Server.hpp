#ifndef SERVER_HPP
#define SERVER_HPP

#include <boost/asio.hpp>
#include "IServer.hpp"

class Server : public IServer
{
  public: // --- Constructor ---
    Server(boost::asio::io_context &              _IOContext,
           const boost::asio::ip::tcp::endpoint & _Endpoint);

  private: // Service
    void DoAccept() override;
};

#endif // SERVER_HPP