#ifndef MESSAGE_BLOCK_HPP
#define MESSAGE_BLOCK_HPP

#include "MessageBlockDescriptor.hpp"
#include <memory>

class MessageBlock;

typedef std::shared_ptr<MessageBlock> MessageBlockPtr;

class MessageBlock
{
  public: // --- Constructor / Destructor ---
  MessageBlock(MessageBlockDescriptor m_Descriptor);

  ~MessageBlock();

  public: // --- Interface ---
    const MessageBlockDescriptor & GetDescriptor() const;

    uint8_t GetBlockID() const;

    int32_t GetMessageID() const;

    uint16_t GetBodySize() const;

    uint16_t GetDataSize() const;

    char * GetBody();

    const char * GetBody() const;

    void * GetStartDataAddress() const;

  public: // --- Constants ---
    static constexpr size_t MAX_BODY_SIZE   = 10;
    static constexpr size_t DESCRIPTOR_SIZE = sizeof(MessageBlockDescriptor);

  private: // --- Member variables ---
    MessageBlockDescriptor m_Descriptor;
    char                   m_Body[MAX_BODY_SIZE];
};

#endif //MESSAGE_BLOCK_HPP