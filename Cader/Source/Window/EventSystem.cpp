#include "Cader/Window/EventSystem.h"

#include <assert.h>

namespace CDR {

	Event EventSystem::sEvents[MaxEvents] = {};
	u8 EventSystem::sCount = 0;

	void EventSystem::FireEvent(Event pEvent, bool pPriority)
	{
		if(sCount >= MaxEvents)
		{
			if(pPriority)
				sEvents[0] = pEvent;

			return;
		}

		sEvents[sCount++] = pEvent;
	}

	Event EventSystem::GetEvent(u8 pIndex)
	{
		assert(pIndex < sCount);
		return sEvents[pIndex];
	}

	void EventSystem::Release()
	{
		sCount = 0;
	}

}