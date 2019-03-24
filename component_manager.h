#pragma once
#include "common.h"

struct BaseComponent;



class ComponentManager
{



public:
	struct ComponentInfo
	{
		void* prototype;//sample
		size_t size;
	};
	static ComponentInfo m_infos[kMaxComponentCount];


	struct EntityID
	{
		uint32 archetype;
		uint32 chunk;
		uint32 id;
	};
	static std::vector<EntityID> m_IDs;


	template<typename T>
	static constexpr void InitComponent()
	{
		//todo: static assert
		//static_assert(Component<T>::ID < kMaxComponentCount, "number of components is more than max_component_count");
		static_assert(std::is_base_of<BaseComponent, T>::value, "");
		m_infos[T::ID] = {(void*)&T::kPrototype, sizeof(T)};
	}

private:
	template<typename T>
	static constexpr int SetBit(Bittype &bittype)
	{
		ComponentManager::InitComponent<T>();
		bittype[T::ID] = 1;
		return 0;
	}

public:
	template<typename ...Ts>
	static constexpr Bittype ToBittype()
	{
		Bittype bittype;
		int ids[]{SetBit<Ts>(bittype)...};
		return bittype;
	}

	static array GetIds(Bittype bittype);


};
