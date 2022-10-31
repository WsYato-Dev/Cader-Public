#pragma once

#include "Cader/Types/Common.h"

namespace CDR {

	using Milliseconds = u32;

	class Engine;

	class Time final
	{
		friend Engine;

		static Milliseconds sNow;
		static float sDelta;

		static void Init();
		static void Update();

	public:
		static inline Milliseconds Now() noexcept { return sNow; }
		static inline float Delta() noexcept { return sDelta; }
	};

	struct Timer final
	{
	private:
		Milliseconds mEnd = 0;

	public:
		inline void Start(Milliseconds pMilliseconds)
		{
			mEnd = pMilliseconds + Time::Now();
		}

		inline bool Check() const noexcept
		{
			return mEnd <= Time::Now();
		}
	};

	struct StopWatch final
	{
	private:
		Milliseconds mStart = 0;

	public:
		inline void Start()
		{
			mStart = Time::Now();
		}

		inline Milliseconds Elapsed() const noexcept
		{
			return Time::Now() - mStart;
		}
	};

}