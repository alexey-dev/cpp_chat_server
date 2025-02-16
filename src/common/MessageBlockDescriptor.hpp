#ifndef MESSAGE_BLOCK_DESCRIPTOR_HPP
#define MESSAGE_BLOCK_DESCRIPTOR_HPP

#include <iostream>

struct MessageBlockDescriptor
{
  int32_t  MessageID;
  uint16_t BodySize;
  uint8_t  CountBlocks;
  uint8_t  BlockID;
};

#endif //MESSAGE_BLOCK_DESCRIPTOR_HPP