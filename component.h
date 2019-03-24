#pragma once
#include "common.h"

struct BaseComponent
{
	static uint16 ComponentCount;
};

uint16 BaseComponent::ComponentCount(0);

template<typename T>
struct Component : BaseComponent
{
	static const uint16 ID;
	static const T kPrototype;
};

template<typename T>
const T Component<T>::kPrototype = T();

template<typename T>
const uint16 Component<T>::ID(BaseComponent::ComponentCount++);