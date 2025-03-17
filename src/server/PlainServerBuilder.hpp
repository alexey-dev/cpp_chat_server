#ifndef PLAIN_SERVER_BUILDER_HPP
#define PLAIN_SERVER_BUILDER_HPP

#include "IServerBuilder.hpp"

class PlainServerBuilder : public IServerBuilder
{
  public: // --- Constructor/Destructor ---
    PlainServerBuilder(const InputArguments &    _Arguments,
                       boost::asio::io_context & _IOContext);

  public: // --- Interface ---
    void InitServerSetup() override;

    void InitSpecificSettings() override;
};

#endif // PLAIN_SERVER_BUILDER_HPP