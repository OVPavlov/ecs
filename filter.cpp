#include "filter.h"

Filter* Filter::Create(Bittype bittype)
{
	auto ids = ComponentManager::GetIds(bittype);
	Filter* filter = new Filter();
	filter->m_bittype = bittype;
	filter->m_componentCount = ids.count;
	filter->m_componentIDs = new uint16[ids.count];
	for (uint16 i = 0; i < ids.count; ++i)
		filter->m_componentIDs[i] = ids.ptr[i];

	static std::vector<Archetype*> arhetypes;
	ArchetypeManager::Filter(arhetypes, bittype);
	for (auto const& arhetype : arhetypes)	
		filter->AddArchetype(arhetype);	

	return filter;
}

void Filter::AddArchetype(Archetype * archetype)
{
	ArchetypeReference ar = ArchetypeReference();

	ar.archetype = archetype;
	ar.bittype = archetype->m_bitType;
	ar.offsets = new size_t[m_componentCount];
	archetype->GetOffsets(ar.offsets, m_componentIDs, m_componentCount);
	m_archetypes.push_back(ar);
}

char* Filter::GetNextChunk(uint16 &archetypeNum, uint16 &chunkNum)
{
	while (archetypeNum < m_archetypes.size())
	{
		auto ar = m_archetypes[archetypeNum];
		char* chunk = ar.archetype->GetChunk(chunkNum);
		if (chunk == nullptr)
		{
			++archetypeNum;
			chunkNum = 0;
			continue;
		}
		else
		{
			++chunkNum;
			return chunk;
		}
	}
	chunkNum = 0;
	archetypeNum = 0;
	return nullptr;
}

bool Filter::InitializeNextChunk(char ** firstCompPtr, uint16 & archetypeNum, uint16 & chunkNum)
{
	char* chunk = GetNextChunk(archetypeNum, chunkNum);
	if(!chunk) return false;

	auto ar = m_archetypes[archetypeNum];

	for (uint16 i = 0; i < m_componentCount; i++)
		firstCompPtr[i] = chunk + ar.offsets[i];

	return true;
}
