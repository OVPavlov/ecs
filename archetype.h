#pragma once
#include "common.h"
#include "component_manager.h"
#include "archetype_manager.h"


class Archetype
{
	struct ComponentArray
	{
		size_t offset;
		uint16 elementSize;
		uint16 elementID;
	};
	ComponentArray* m_componens;
	uint16 m_componentCount;

	size_t m_chunkCapacity;
	size_t m_lastChunkSize;
	std::vector<char*> m_chunks;

public:	
	Bittype m_bitType;

	static Archetype* Create(Bittype &bittype);

	template<typename ...Ts>
	static Archetype* Create()
	{
		Bittype bittype = ComponentManager::ToBittype<Ts...>();
		return Create(bittype);
	}

	void GetOffsets(size_t* offsets, uint16* ids, uint16 count);

	char* GetChunk(size_t num);

	template<typename T>
	void AddComponent(uint32 id)
	{
		// initialize new type if needed
		// take typeBits
		// get existing archetype
		//		or create a new one
		// remove an entity from this archetype and add to the new one
		// copy all components we have + copy prototypes we don't
		// initialize new array position for it

	}

	void RemoveEntity(uint32 id)
	{
		//place the last entity to the id place
		//move id of idArray
		//reassign id in global id Array;
	}

	uint32 AddEntity();
};
