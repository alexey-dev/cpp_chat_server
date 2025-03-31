#ifndef PLAIN_CLIENT_HPP
#define PLAIN_CLIENT_HPP

#include "IClient.hpp"

class PlainClient : public IClient
{
  public: // --- Constructor ---
    PlainClient(boost::asio::io_context &                            _IOContext,
                const boost::asio::ip::tcp::resolver::results_type & _Endpoints,
                const LoginData &                                    _LoginData);

  public: // --- Interface ---
    void Close() override;

  private: // --- Service ---
    void DoConnect(const boost::asio::ip::tcp::resolver::results_type & _Endpoints) override;

    void DoLogin() override;

    void DoWrite() override;

    void PostWrite() override;

    void DoReadDescriptor() override;

    void DoReadBody() override;

  private: // --- Member variables ---
    boost::asio::ip::tcp::socket m_Socket;
};

#endif // PLAIN_CLIENT_HPP