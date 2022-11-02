#include "Cader/Window/EventSystem.h"

#include <assert.h>

namespace CDR {

	void EventSystem::FireEvent(Event pEvent, bool pPriority)
	{
		if(mCount >= MaxEvents)
		{
			if(pPriority)
				mEvents[0] = pEvent;

			return;
		}

		mEvents[mCount++] = pEvent;
	}

	Event EventSystem::GetEvent(u8 pIndex)
	{
		assert(pIndex < mCount);
		return mEvents[pIndex];
	}

	void EventSystem::Release()
	{
		mCount = 0;
	}

}