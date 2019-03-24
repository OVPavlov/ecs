#pragma once
#include "common.h"
#include "component_manager.h"
#include "archetype.h"
#include "component_iterator.h"


class Filter
{
	Bittype m_bittype;
	uint16 m_componentCount;
	uint16* m_componentIDs;

	struct ArchetypeReference
	{
		Bittype bittype;
		Archetype* archetype;
		size_t* offsets;
	};
	std::vector<ArchetypeReference> m_archetypes;

	char* GetNextChunk(uint16 &archetypeNum, uint16 &chunkNum);

public:	
	
	static Filter* Create(Bittype bittype);

	void AddArchetype(Archetype* archetype);

	bool InitializeNextChunk(char** firstCompPtr, uint16 &archetypeNum, uint16 &chunkNum);
};
