#ifndef CINPUT_ARGUMENTS_HPP
#define CINPUT_ARGUMENTS_HPP

#include <string>

struct InputArguments
{
  std::string Host;
  std::string CertificateSSLPath;
  int         Port;
  bool        IsSSLActive;
};

#endif //CINPUT_ARGUMENTS_HPP