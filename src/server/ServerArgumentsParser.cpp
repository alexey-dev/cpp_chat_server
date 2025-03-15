#include "ServerArgumentsParser.hpp"
#include <iostream>

// --- Constants ---
const char * ServerArgumentsParser::HELP_KEY        = "help";
const char * ServerArgumentsParser::PORT_KEY        = "port";
const char * ServerArgumentsParser::SSL_KEY         = "ssl";
const char * ServerArgumentsParser::PRIVATE_KEY_KEY = "key";
const char * ServerArgumentsParser::CERT_KEY        = "cert";

// --- Constructor ---
ServerArgumentsParser::ServerArgumentsParser() :
  m_Description("Allowed options info"),
  m_Arguments({"", "", -1, false})
{
  m_Description.add_options()
      (HELP_KEY,         "[optional] show help message")
      (PORT_KEY,         boost::program_options::value<int>(),         "set port")
      (SSL_KEY,          "[optional] activate SSL mode")
      (PRIVATE_KEY_KEY,  boost::program_options::value<std::string>(), "[optional] path to private key for SSL")
      (CERT_KEY,         boost::program_options::value<std::string>(), "[optional] path to certificate for SSL");
}

// --- Interface ---
bool ServerArgumentsParser::Parse(int _Argc,
                                  char * _Argv[])
{
  boost::program_options::variables_map VariablesMap;
  boost::program_options::store(boost::program_options::parse_command_line(_Argc, _Argv, m_Description), VariablesMap);
  boost::program_options::notify(VariablesMap);

  if (VariablesMap.count(HELP_KEY))
  {
      std::cout << m_Description << std::endl;
      return false;
  }

  if (!VariablesMap.count(PORT_KEY))
  {
    std::cout << "Error: no port.\n" << m_Description << std::endl;
    return false;
  }

  m_Arguments.Port = VariablesMap[PORT_KEY].as<int>();

  if (!VariablesMap.count(SSL_KEY))
    return true;

  if (!VariablesMap.count(PRIVATE_KEY_KEY) || !VariablesMap.count(CERT_KEY))
  {
    std::cout << "Error: no paths for ssl mode.\n" << m_Description << std::endl;
    return false;
  }

  m_Arguments.IsSSLActive        = true;
  m_Arguments.PrivateKeySSLPath  = VariablesMap[PRIVATE_KEY_KEY].as<std::string>();
  m_Arguments.CertificateSSLPath = VariablesMap[CERT_KEY].as<std::string>();

  return true;
}

const InputArguments & ServerArgumentsParser::GetArguments() const
{
  return m_Arguments;
}