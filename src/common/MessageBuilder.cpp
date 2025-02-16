#include "MessageBuilder.hpp"
#include <cmath>

static int32_t MessagesCounter = 1;

// --- Interface ---
std::vector<MessageBlockPtr> MessageBuilder::CreateBlocksFromRawMessage(char * _Data)
{
  std::vector<MessageBlockPtr> VecBlocks;
  const size_t                 DataLen     = strlen(_Data);
  const uint8_t                CountBlocks = std::ceil(static_cast<float>(DataLen) / MessageBlock::MAX_BODY_SIZE);
  char *                       DataPtr     = _Data;

  for (size_t i = 0; i < CountBlocks; i++)
  {
    const size_t   LeftBytes = strlen(DataPtr);
    const uint16_t BlockSize = LeftBytes > MessageBlock::MAX_BODY_SIZE ? MessageBlock::MAX_BODY_SIZE : LeftBytes;

    MessageBlockDescriptor CurrentDescriptor{MessagesCounter, BlockSize, CountBlocks, static_cast<uint8_t>(i+1)};
    MessageBlockPtr        CurrentBlock = std::make_shared<MessageBlock>(CurrentDescriptor);

    memcpy(CurrentBlock->GetBody(), DataPtr, BlockSize);
    VecBlocks.push_back(CurrentBlock);

    DataPtr += BlockSize;
  }

  MessagesCounter++;

  return VecBlocks;
}
