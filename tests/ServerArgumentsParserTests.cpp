#include "../src/server/ServerArgumentsParser.hpp"
#include "gtest/gtest.h"

namespace {

TEST(ServerArgumentsParserTest, Parse_PassHelpWithoutValue_ReturnsFalse) {
  ServerArgumentsParser Parser;
  char      Argv0[] = "path/to/executable";
  char      Argv1[] = "--help";
  char *    Argv[]  = {Argv0, Argv1};
  const int Argc    = sizeof(Argv)/sizeof(char*);

  EXPECT_FALSE(Parser.Parse(Argc, Argv));
}

TEST(ServerArgumentsParserTest, Parse_PassHelpAndPort_ReturnsFalse) {
  ServerArgumentsParser Parser;
  char      Argv0[] = "path/to/executable";
  char      Argv1[] = "--help";
  char      Argv2[] = "--port";
  char      Argv3[] = "10001";
  char *    Argv[]  = {Argv0, Argv1, Argv2, Argv3};
  const int Argc    = sizeof(Argv)/sizeof(char*);

  EXPECT_FALSE(Parser.Parse(Argc, Argv));
}

TEST(ServerArgumentsParserTest, Parse_PassPortWithNumericValue_ReturnsTrue) {
  ServerArgumentsParser Parser;
  char      Argv0[] = "path/to/executable";
  char      Argv1[] = "--port";
  char      Argv2[] = "10001";
  char *    Argv[]  = {Argv0, Argv1, Argv2};
  const int Argc    = sizeof(Argv)/sizeof(char*);

  EXPECT_TRUE(Parser.Parse(Argc, Argv));
}

TEST(ServerArgumentsParserTest, Parse_PortMissing_ReturnsFalse) {
  ServerArgumentsParser Parser;
  char      Argv0[] = "path/to/executable";
  char *    Argv[]  = {Argv0};
  const int Argc    = sizeof(Argv)/sizeof(char*);

  EXPECT_FALSE(Parser.Parse(Argc, Argv));
}

TEST(ServerArgumentsParserTest, Parse_PassPortSSLAndCertificatePathAndPrivateKeyPathMissing_ReturnsFalse) {
  ServerArgumentsParser Parser;
  char      Argv0[] = "path/to/executable";
  char      Argv1[] = "--port";
  char      Argv2[] = "10001";
  char      Argv3[] = "--ssl";
  char *    Argv[]  = {Argv0, Argv1, Argv2, Argv3};
  const int Argc    = sizeof(Argv)/sizeof(char*);

  EXPECT_FALSE(Parser.Parse(Argc, Argv));
}

TEST(ServerArgumentsParserTest, Parse_PassPortSSLAndPrivateKeyPathMissing_ReturnsFalse) {
  ServerArgumentsParser Parser;
  char      Argv0[] = "path/to/executable";
  char      Argv1[] = "--port";
  char      Argv2[] = "10001";
  char      Argv3[] = "--ssl";
  char      Argv4[] = "--cert";
  char      Argv5[] = "sslkeys/selfsigned.key";
  char *    Argv[]  = {Argv0, Argv1, Argv2, Argv3, Argv4, Argv5};
  const int Argc    = sizeof(Argv)/sizeof(char*);

  EXPECT_FALSE(Parser.Parse(Argc, Argv));
}

TEST(ServerArgumentsParserTest, Parse_PassPortSSLAndCertificatePathMissing_ReturnsFalse) {
  ServerArgumentsParser Parser;
  char      Argv0[] = "path/to/executable";
  char      Argv1[] = "--port";
  char      Argv2[] = "10001";
  char      Argv3[] = "--ssl";
  char      Argv4[] = "--key";
  char      Argv5[] = "sslkeys/private.key";
  char *    Argv[]  = {Argv0, Argv1, Argv2, Argv3, Argv4, Argv5};
  const int Argc    = sizeof(Argv)/sizeof(char*);

  EXPECT_FALSE(Parser.Parse(Argc, Argv));
}

TEST(ServerArgumentsParserTest, Parse_PassPortSSLCertificatePathPrivateKeyPath_ReturnsTrue) {
  ServerArgumentsParser Parser;
  char      Argv0[] = "path/to/executable";
  char      Argv1[] = "--port";
  char      Argv2[] = "10001";
  char      Argv3[] = "--ssl";
  char      Argv4[] = "--key";
  char      Argv5[] = "sslkeys/private.key";
  char      Argv6[] = "--cert";
  char      Argv7[] = "sslkeys/selfsigned.key";
  char *    Argv[]  = {Argv0, Argv1, Argv2, Argv3, Argv4, Argv5, Argv6, Argv7};
  const int Argc    = sizeof(Argv)/sizeof(char*);

  EXPECT_TRUE(Parser.Parse(Argc, Argv));
}

}  // namespace