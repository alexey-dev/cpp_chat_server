#include "../src/common/MessageBuilder.hpp"
#include "../src/common/MessageBlock.hpp"
#include "../src/common/Message.hpp"
#include <memory>
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

TEST(MessageTest, HasAllBlocks_EmptyMessage_ReturnsFalse) {
  MessagePtr MessageObj = std::make_shared<Message>();

  EXPECT_FALSE(MessageObj->HasAllBlocks());
}

TEST(MessageTest, HasAllBlocks_AddFiveBlocksOfFive_ReturnsTrue) {
  MessageBuilder   Builder;
  constexpr int8_t CountBlocks = 5;
  std::string      MessageRaw(CountBlocks * MessageBlock::MAX_BODY_SIZE, 'a');
  auto             Blocks      = Builder.CreateBlocksFromRawMessage(MessageRaw.data());
  MessagePtr       MessageObj  = std::make_shared<Message>();

  for (const auto & Block : Blocks)
    MessageObj->AddBlock(Block);

  EXPECT_TRUE(MessageObj->HasAllBlocks());
}

TEST(MessageTest, HasAllBlocks_AddOneBlockOfTwo_ReturnsFalse) {
  MessageBuilder   Builder;
  constexpr int8_t CountBlocks = 2;
  std::string      MessageRaw(CountBlocks * MessageBlock::MAX_BODY_SIZE, 'a');
  auto             Blocks      = Builder.CreateBlocksFromRawMessage(MessageRaw.data());
  MessagePtr       MessageObj  = std::make_shared<Message>();

  MessageObj->AddBlock(Blocks[0]);

  EXPECT_FALSE(MessageObj->HasAllBlocks());
}

TEST(MessageTest, GetVectorOfBlocks_CheckAddingTwoBlocks_ReturnsTwoBlocks) {
  MessageBuilder   Builder;
  constexpr int8_t CountBlocks = 2;
  std::string      MessageRaw(CountBlocks * MessageBlock::MAX_BODY_SIZE, 'a');
  auto             Blocks      = Builder.CreateBlocksFromRawMessage(MessageRaw.data());
  MessagePtr       MessageObj  = std::make_shared<Message>();

  for (const auto & Block : Blocks)
    MessageObj->AddBlock(Block);

  EXPECT_TRUE(MessageObj->GetVectorOfBlocks().size() == 2);
}

}  // namespace