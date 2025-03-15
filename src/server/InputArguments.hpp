#ifndef INPUT_ARGUMENTS_HPP
#define INPUT_ARGUMENTS_HPP

#include <string>

struct InputArguments
{
  std::string PrivateKeySSLPath;
  std::string CertificateSSLPath;
  int         Port;
  bool        IsSSLActive;
};

#endif //INPUT_ARGUMENTS_HPP