#pragma once
#include "common.h"


class Filter;

template <typename... Ts>
struct BaseComponentIterator
{
	Filter* filter;
	uint16 archetype_num;
	uint16 chunk_num;
	uint* index;
	uint* indexEnd;

	inline bool Iterate();
};

template <typename...> struct ComponentIterator;

template<typename T0>
struct ComponentIterator<T0> : BaseComponentIterator<T0>
{
	T0* comp0;
	inline bool Next()
	{
		++comp0;
		return this->Iterate();
	}
};


template<typename ...Ts>
inline bool BaseComponentIterator<Ts...>::Iterate()
{
	if (++index == indexEnd)
	{
		char** firstComponent = (char**)((char*)this + offsetof(ComponentIterator<int>, comp0));
		return filter->InitializeNextChunk(firstComponent, archetype_num, chunk_num);
	}
	return true;
}

template<typename T0, typename T1>
struct ComponentIterator<T0, T1> : BaseComponentIterator<T0, T1>
{
	T0* comp0; T1* comp1;
	inline bool Next()
	{
		++comp0; ++comp1;
		return this->Iterate();
	}
};

template<typename T0, typename T1, typename T2>
struct ComponentIterator<T0, T1, T2> : BaseComponentIterator<T0, T1, T2>
{
	T0* comp0; T1* comp1; T2* comp2;
	inline bool Next()
	{
		++comp0; ++comp1; ++comp2;
		return this->Iterate();
	}
};
