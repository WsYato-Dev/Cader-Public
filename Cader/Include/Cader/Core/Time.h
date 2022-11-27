#pragma once

#include "Cader/Types/Common.h"

namespace CDR {

	using Milliseconds = u32;

	class Engine;

	class Time final
	{
		static void Init();
		static void Update();
		static void Recaliber();

	public:
		static Milliseconds Now() noexcept { return sNow; }
		static float Delta() noexcept { return sDelta; }

	private:
		static Milliseconds sNow;
		static float sDelta;

		friend Engine;
	};

	struct Timer final
	{
		void Start(Milliseconds pMilliseconds) { mEnd = pMilliseconds + Time::Now(); }
		bool Check() const noexcept { return mEnd <= Time::Now(); }

	private:
		Milliseconds mEnd{0};
	};

	struct StopWatch final
	{
		void Start() { mStart = Time::Now(); }
		Milliseconds Elapsed() const noexcept { return Time::Now() - mStart; }

	private:
		Milliseconds mStart{0};
	};

#if !defined(CDR_FINAL)

	struct INTERNAL_FunctionBenchmarker final
	{
		INTERNAL_FunctionBenchmarker(Text pFunction);
		~INTERNAL_FunctionBenchmarker();

	private:
		const Text mFunction;
		u64 mStart;
	};

#endif

}

#if !defined(CDR_FINAL)

#define CDR_INTERNAL_PROFILE(func, line) { CDR::INTERNAL_FunctionBenchmarker benchmarker##line(#func); func; }
#define CDR_INTERNAL_PROFILE_EXPANDED(func, line) CDR_INTERNAL_PROFILE(func, line)
#define CDR_PROFILE(func) CDR_INTERNAL_PROFILE_EXPANDED(func, __LINE__)

#else

#define CDR_PROFILE(func)

#endif