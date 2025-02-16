#ifndef MESSAGE_BUILDER_HPP
#define MESSAGE_BUILDER_HPP

#include "Message.hpp"
#include "MessageBlock.hpp"
#include "MessageBlockDescriptor.hpp"
#include <vector>

class MessageBuilder
{
  public: // --- Interface ---
    std::vector<MessageBlockPtr> CreateBlocksFromRawMessage(char * _Data);
};

#endif //MESSAGE_BUILDER_HPP