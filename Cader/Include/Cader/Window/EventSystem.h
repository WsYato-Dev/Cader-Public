#pragma once

#include "Cader/Types/Common.h"
#include "Cader/Window/Event.h"

namespace CDR {

	class Engine;

	class EventSystem final
	{
		friend Engine;

	public:
		static constexpr u8 MaxEvents = 5;

	private:
		static Event sEvents[MaxEvents];
		static u8 sCount;

		Event GetEvent(u8 pIndex);
		void Release();

	public:
		static void FireEvent(Event pEvent, bool pPriority = false);

		static inline u8 Count() noexcept { return sCount; }
		static inline bool IsEmpty() noexcept { return sCount <= 0; }
	};

}