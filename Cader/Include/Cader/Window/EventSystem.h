#pragma once

#include "Cader/Types/Common.h"
#include "Cader/Window/Event.h"

namespace CDR {

	class EventSystem final
	{
	public:
		static constexpr u8 MaxEvents = 5;

	private:
		Event mEvents[MaxEvents];
		u8 mCount = 0;

	public:
		void FireEvent(Event pEvent, bool pPriority = false);
		Event GetEvent(u8 pIndex);

		void Release();

		inline u8 Count() const noexcept { return mCount; }
		inline bool IsEmpty() const noexcept { return mCount <= 0; }
	};

}