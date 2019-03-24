#include "pool.h"

Pool::Pool(uint bytes)
{
	m_elementSize = bytes;
	m_free.reserve(256);
}

size_t Pool::GetElementSize()
{
	return m_elementSize;
}

char * Pool::Get()
{
	if (m_free.empty())
		return (char*)malloc(m_elementSize);
	
	char* chunk = m_free.back();
	m_free.pop_back();
	return chunk;
}

void Pool::Release(char * data)
{
	m_free.push_back(data);
}
