#include "MessageBlock.hpp"

// --- Constructor / Destructor ---
MessageBlock::MessageBlock(MessageBlockDescriptor _Descriptor) :
  m_Descriptor(_Descriptor)
{
}

MessageBlock::~MessageBlock()
{
}

// --- Interface ---
const MessageBlockDescriptor & MessageBlock::GetDescriptor() const
{
  return m_Descriptor;
}

uint8_t MessageBlock::GetBlockID() const
{
  return GetDescriptor().BlockID;
}

int32_t MessageBlock::GetMessageID() const
{
  return GetDescriptor().MessageID;
}

uint16_t MessageBlock::GetBodySize() const
{
  return GetDescriptor().BodySize;
}

uint16_t MessageBlock::GetDataSize() const
{
  return (DESCRIPTOR_SIZE + GetBodySize());
}

char * MessageBlock::GetBody()
{
  return m_Body;
}

const char * MessageBlock::GetBody() const
{
  return m_Body;
}

void * MessageBlock::GetStartDataAddress() const
{
  return (void *)std::addressof(m_Descriptor);
}
