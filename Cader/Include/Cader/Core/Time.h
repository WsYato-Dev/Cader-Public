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
		static void Recaliber();

	public:
		static inline Milliseconds Now() noexcept { return sNow; }
		static inline float Delta() noexcept { return sDelta; }
	};

	struct Timer final
	{
	private:
		Milliseconds mEnd{0};

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
		Milliseconds mStart{0};

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

#if !defined(CDR_FINAL)

	struct INTERNAL_FunctionBenchmarker final
	{
	private:
		const Text mFunction;
		u64 mStart;

	public:
		INTERNAL_FunctionBenchmarker(Text pFunction);
		~INTERNAL_FunctionBenchmarker();
	};

#endif

}

#if !defined(CDR_FINAL)

#define CDR_INTERNAL_PROFILE_FUNCTION(func, line) { CDR::INTERNAL_FunctionBenchmarker benchmarker##line(#func); func; }
#define CDR_INTERNAL_PROFILE_FUNCTION_EXPANDED(func, line) CDR_INTERNAL_PROFILE_FUNCTION(func, line)
#define CDR_PROFILE_FUNCTION(func) CDR_INTERNAL_PROFILE_FUNCTION_EXPANDED(func, __LINE__)

#else

#define CDR_PROFILE_FUNCTION(func)

#endif