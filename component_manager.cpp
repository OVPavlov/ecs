#include "component_manager.h"


ComponentManager::ComponentInfo ComponentManager::m_infos[kMaxComponentCount];

array ComponentManager::GetIds(Bittype bittype)
{
	static uint16 ids[kMaxComponentCount];
	uint16 count = 0;
	for (uint16 cID = 0; cID != kMaxComponentCount; ++cID)
		if (bittype[cID])		
			ids[count++] = cID;		
	return {ids, count};
}
