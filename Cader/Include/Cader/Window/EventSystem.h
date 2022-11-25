#pragma once

#include "Cader/Types/Common.h"
#include "Cader/Utility/Assert.h"
#include "Cader/Window/Event.h"

namespace CDR {

	class Engine;

	class EventSystem final
	{
		static Event GetEvent(const u8 pIndex)
		{
			CDR_ASSERT(sCount >= pIndex);
			return sEvents[pIndex];
		}

		static void Release()
		{
			sCount = 0;
		}

	public:
		static void FireEvent(const Event pEvent, const bool pPriority = false)
		{
			if(MaxEvents <= sCount)
			{
				if(pPriority)
					sEvents[0] = pEvent;

				return;
			}

			sEvents[sCount++] = pEvent;
		}

		static u8 Count() noexcept { return sCount; }
		static bool IsEmpty() noexcept { return 0 >= sCount; }

		static constexpr u8 MaxEvents{5};

	private:
		static inline Event sEvents[MaxEvents];
		static inline u8 sCount{0};

		friend Engine;
	};

}