#ifndef SERVER_ARGUMENTS_PARSER_HPP
#define SERVER_ARGUMENTS_PARSER_HPP

#include "InputArguments.hpp"
#include <boost/program_options.hpp>

class ServerArgumentsParser
{
  public: // --- Constructor ---
    ServerArgumentsParser();

  public: // --- Interface ---
    bool Parse(int _Argc,
               char * _Argv[]);

    const InputArguments & GetArguments() const;

  private: // --- Constants ---
    static const char * HELP_KEY;
    static const char * PORT_KEY;
    static const char * SSL_KEY;
    static const char * PRIVATE_KEY_KEY;
    static const char * CERT_KEY;

  private: // --- Member variables ---
    InputArguments                              m_Arguments;
    boost::program_options::options_description m_Description;
};

#endif //SERVER_ARGUMENTS_PARSER_HPP