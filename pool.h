#pragma once
#include "common.h"



class Pool
{
	size_t m_elementSize;
	std::vector<char*> m_free;

public:
	Pool(uint bytes);

	size_t GetElementSize();

	char* Get();

	void Release(char* data);
};