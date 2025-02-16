#include "Message.hpp"
#include "MessageBlockDescriptor.hpp"

std::string Message::GetBody() const
{
  return m_Body;
}

void Message::AddBlock(const MessageBlockPtr _Block)
{
  m_Blocks[_Block->GetBlockID()] = _Block;

  TryGatherBlocks();
}

bool Message::HasAllBlocks() const
{
  if (m_Blocks.empty())
    return false;

  const MessageBlockDescriptor & FirstDescriptor = m_Blocks.begin()->second->GetDescriptor();

  return (FirstDescriptor.CountBlocks == m_Blocks.size());
}

std::vector<MessageBlockPtr> Message::GetVectorOfBlocks() const
{
  std::vector<MessageBlockPtr> VecBlocks;
  VecBlocks.reserve(m_Blocks.size());

  for (const auto & ItPair : m_Blocks)
    VecBlocks.push_back(ItPair.second);

  return VecBlocks;
}

// --- Service ---
void Message::TryGatherBlocks()
{
  if (!m_Body.empty() || !HasAllBlocks())
    return;

  for (const auto & BlockPairPtr : m_Blocks)
    m_Body.append(BlockPairPtr.second->GetBody());
}
