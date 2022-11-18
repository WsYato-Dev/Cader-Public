#pragma once

#include "Cader/Types/Common.h"
#include "Cader/Utility/Assert.h"
#include "Cader/Window/Event.h"

namespace CDR {

	class Engine;

	class EventSystem final
	{
		friend Engine;

	public:
		static constexpr u8 MaxEvents{5};

	private:
		static inline Event sEvents[MaxEvents];
		static inline u8 sCount{0};

		inline Event GetEvent(u8 pIndex)
		{
			CDR_ASSERT(pIndex < sCount);
			return sEvents[pIndex];
		}

		inline void Release()
		{
			sCount = 0;
		}

	public:
		static inline void FireEvent(Event pEvent, bool pPriority = false)
		{
			if(sCount >= MaxEvents)
			{
				if(pPriority)
					sEvents[0] = pEvent;

				return;
			}

			sEvents[sCount++] = pEvent;
		}

		static inline u8 Count() noexcept { return sCount; }
		static inline bool IsEmpty() noexcept { return sCount <= 0; }
	};

}