#include "../src/common/MessageBuilder.cpp"
#include "../src/common/MessageBlock.cpp"
#include "gtest/gtest.h"

namespace {

TEST(MessageBuilderTest, CreateBlocksFromRawMessage_PassTenBodies_ReturnsTenBlocks) {
  MessageBuilder   Builder;
  constexpr int8_t CountBlocks = 10;
  std::string      Message(CountBlocks * MessageBlock::MAX_BODY_SIZE, 'a');

  auto Blocks = Builder.CreateBlocksFromRawMessage(Message.data());

  EXPECT_EQ(Blocks.size(), CountBlocks);
}

TEST(MessageBuilderTest, CreateBlocksFromRawMessage_PassEmptyBody_ReturnsNullBlocks) {
  MessageBuilder Builder;
  std::string    Message;

  auto Blocks = Builder.CreateBlocksFromRawMessage(Message.data());

  EXPECT_TRUE(Blocks.empty());
}

}  // namespace