#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <iostream>

class Message
{
  public: //Interface
    Message();

    ~Message();

    char * GetBody();

    const char * GetBody() const;

  public: // Constants
    static constexpr size_t MAX_BODY_SIZE = 256;

  private:
    char m_Body[MAX_BODY_SIZE];
};

#endif // MESSAGE_HPP
