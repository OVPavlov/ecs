#pragma once
#include "common.h"
#include "pool.h"

class Archetype;

class ArchetypeManager
{
public:
	static std::unordered_map<Bittype, Archetype*> m_arhetypes;
	static std::map<Bittype, int> m_filters;
	static Pool m_pool;

	static Archetype* Get(Bittype &bittype);

	static void Filter(std::vector<Archetype*> &arhetypes, Bittype &bittype);

	static void Add(Archetype* arhetype);
};

