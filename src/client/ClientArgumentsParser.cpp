#include "ClientArgumentsParser.hpp"
#include <iostream>

// --- Constants ---
const char * ClientArgumentsParser::HELP_KEY        = "help";
const char * ClientArgumentsParser::HOST_KEY        = "host";
const char * ClientArgumentsParser::PORT_KEY        = "port";
const char * ClientArgumentsParser::SSL_KEY         = "ssl";
const char * ClientArgumentsParser::CERT_KEY        = "cert";

// --- Constructor ---
ClientArgumentsParser::ClientArgumentsParser() :
  m_Description("Allowed options info"),
  m_Arguments({"", "", -1, false})
{
  m_Description.add_options()
      (HELP_KEY,         "[optional] show help message")
      (HOST_KEY,         boost::program_options::value<std::string>(), "connection host")
      (PORT_KEY,         boost::program_options::value<int>(),         "connection port")
      (SSL_KEY,          "[optional] activate SSL mode")
      (CERT_KEY,         boost::program_options::value<std::string>(), "[optional] path to certificate for SSL");
}

// --- Interface ---
bool ClientArgumentsParser::Parse(int _Argc,
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

  if (!VariablesMap.count(HOST_KEY))
  {
    std::cout << "Error: no connection host.\n" << m_Description << std::endl;
    return false;
  }

  if (!VariablesMap.count(PORT_KEY))
  {
    std::cout << "Error: no connection port.\n" << m_Description << std::endl;
    return false;
  }

  m_Arguments.Host = VariablesMap[HOST_KEY].as<std::string>();
  m_Arguments.Port = VariablesMap[PORT_KEY].as<int>();

  if (!VariablesMap.count(SSL_KEY))
    return true;

  if (!VariablesMap.count(CERT_KEY))
  {
    std::cout << "Error: no paths for ssl mode certificate.\n" << m_Description << std::endl;
    return false;
  }

  m_Arguments.IsSSLActive        = true;
  m_Arguments.CertificateSSLPath = VariablesMap[CERT_KEY].as<std::string>();

  return true;
}

const InputArguments & ClientArgumentsParser::GetArguments() const
{
  return m_Arguments;
}