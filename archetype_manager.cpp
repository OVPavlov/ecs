#include "archetype_manager.h"
#include "archetype.h"
#include "pool.h"


std::unordered_map<Bittype, Archetype*> ArchetypeManager::m_arhetypes;
Pool ArchetypeManager::m_pool(kChunkSize);

Archetype * ArchetypeManager::Get(Bittype & bittype)
{
	if (m_arhetypes.count(bittype))
		return m_arhetypes[bittype];
	else
		return nullptr;
}

void ArchetypeManager::Filter(std::vector<Archetype*> &arhetypes, Bittype &bittype)
{
	arhetypes.clear();
	for (const auto& kv : m_arhetypes)
		if ((kv.first & bittype) == bittype)
			arhetypes.push_back(kv.second);
}

void ArchetypeManager::Add(Archetype * arhetype)
{
	m_arhetypes[arhetype->m_bitType] = arhetype;
}
