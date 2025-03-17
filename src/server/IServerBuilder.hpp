#ifndef ISERVER_BUILDER_HPP
#define ISERVER_BUILDER_HPP

#include <boost/asio.hpp>
#include "IServer.hpp"
#include "InputArguments.hpp"

class IServerBuilder
{
  public: // --- Constructor/Destructor ---
    IServerBuilder(const InputArguments &    _Arguments,
                   boost::asio::io_context & _IOContext);

    ~IServerBuilder();

  public: // --- Interface ---
    std::shared_ptr<IServer> GetProduct();

    virtual void InitServerSetup() = 0;

    virtual void InitSpecificSettings() = 0;

  protected: // --- Member variables ---
    std::shared_ptr<IServer>  m_Server;
    const InputArguments &    m_Arguments;
    boost::asio::io_context & m_IOContext;
};

#endif // ISERVER_BUILDER_HPP