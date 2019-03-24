#include "archetype.h"
#include "archetype_manager.h"


Archetype *Archetype::Create(Bittype &bittype)
{
	auto ids = ComponentManager::GetIds(bittype);
	Archetype *archetype = new Archetype();
	archetype->m_componentCount = ids.count;
	archetype->m_bitType = bittype;
	auto componens = archetype->m_componens = new ComponentArray[ids.count];

	size_t all_elements_size = 0;
	for (uint16 i = 0; i < ids.count; ++i)
	{
		componens[i].elementID = ids.ptr[i];
		componens[i].elementSize = ComponentManager::m_infos[ids.ptr[i]].size;
		all_elements_size += componens[i].elementSize;
	}

	size_t chunkSize = ArchetypeManager::m_pool.GetElementSize();
	size_t count = archetype->m_chunkCapacity = (chunkSize / all_elements_size) - 1;
	size_t offset = 0;

	for (uint16 i = 0; i < ids.count; ++i)
	{
		componens[i].offset = offset;
		offset += componens[i].elementSize*count;
	}
	return archetype;
}

void Archetype::GetOffsets(size_t *offsets, uint16 *ids, uint16 count)
{
	ComponentArray* componens = m_componens;
	for (uint16 i = 0; i < count; i++)
	{
		uint16 id = ids[i];
		while (componens->elementID != id) 
			++componens;

		offsets[i] = componens->offset;
	}
}

char* Archetype::GetChunk(size_t num)
{	
	if (num >= m_chunks.size())
		return nullptr;

	return m_chunks[num];
}

uint32 Archetype::AddEntity()
{

	if (m_lastChunkSize == m_chunkCapacity || m_chunks.empty())
	{
		m_lastChunkSize = 0;
		auto chunk = ArchetypeManager::m_pool.Get();
		m_chunks.push_back(chunk);
	}
	char* chunk = m_chunks.back();

	ComponentArray* componens = m_componens;
	ComponentArray* end = componens + m_componentCount;
	for (; componens != end; ++componens)
	{
		auto info = ComponentManager::m_infos[componens->elementID];
		char* ptr = chunk + componens->offset + m_lastChunkSize * info.size;
		memcpy(ptr, info.prototype, info.size);
	}

	//get new id from global id array and do all that stuff
	std::cout << "not implemented entity ID\n";
	return 0;

}
