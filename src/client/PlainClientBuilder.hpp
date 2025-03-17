#ifndef PLAIN_CLIENT_BUILDER_HPP
#define PLAIN_CLIENT_BUILDER_HPP

#include "IClientBuilder.hpp"

class PlainClientBuilder : public IClientBuilder
{
  public: // --- Constructor/Destructor ---
    PlainClientBuilder(const InputArguments &    _Arguments,
                       boost::asio::io_context & _IOContext);

  public: // --- Interface ---
    void InitClientSetup() override;

    void InitSpecificSettings() override;
};

#endif // PLAIN_CLIENT_BUILDER_HPP