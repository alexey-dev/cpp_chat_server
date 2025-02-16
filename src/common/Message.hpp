#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <iostream>
#include "MessageBlock.hpp"
#include <map>
#include <memory>
#include <string>

class Message;

typedef std::shared_ptr<Message> MessagePtr;

class Message
{
  public: // --- Interface ---
    std::string GetBody() const;

    void AddBlock(const MessageBlockPtr _Block);

    bool HasAllBlocks() const;

    std::vector<MessageBlockPtr> GetVectorOfBlocks() const;

  private: // --- Service ---
    void TryGatherBlocks();

  private: // --- Member variables ---
    std::string                        m_Body;
    std::map<uint8_t, MessageBlockPtr> m_Blocks;
};

#endif // MESSAGE_HPP
