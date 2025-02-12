#include "Message.hpp"

Message::Message()
{
}

Message::~Message()
{
}

char * Message::GetBody()
{
  return m_Body;
}

const char * Message::GetBody() const
{
  return m_Body;
}
