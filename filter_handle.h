#pragma once
#include "filter.h"

template <typename... Ts>
class FilterHandle
{
	Filter* m_filter;

public:

	FilterHandle()
	{
		Bittype bittype = ComponentManager::ToBittype<Ts...>();
		m_filter = Filter::Create(bittype);

		std::cout << "test\n";
		
		
	}



	ComponentIterator<Ts...> GenerateIterator()
	{
		ComponentIterator<Ts...> iterator{};
		iterator.index = (uint*)0;
		iterator.indexEnd = iterator.index + 1;
		iterator.filter = m_filter;
		return iterator;
	}


};