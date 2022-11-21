#include "Cader/Core/Time.h"

#include <chrono>
#include <cstdio>

namespace CDR {

	using Clock = std::chrono::steady_clock;
	using TimePoint = Clock::time_point;

	static TimePoint sAppStartTimePoint;
	static TimePoint sLastTickTimePoint;

	Milliseconds Time::sNow{0};
	float Time::sDelta{0.0f};

	void Time::Init()
	{
		sAppStartTimePoint = Clock::now();
		sLastTickTimePoint = sAppStartTimePoint;
	}

	void Time::Update()
	{
		const TimePoint currentTimePoint = Clock::now();

		sNow = (Milliseconds)std::chrono::duration_cast<std::chrono::milliseconds>(currentTimePoint - sAppStartTimePoint).count();
		sDelta = (float)std::chrono::duration_cast<std::chrono::milliseconds>(currentTimePoint - sLastTickTimePoint).count() * 0.001F;

		sLastTickTimePoint = currentTimePoint;
	}

	void Time::Recaliber()
	{
		sLastTickTimePoint = Clock::now();
	}

#if !defined(CDR_FINAL)

	INTERNAL_FunctionBenchmarker::INTERNAL_FunctionBenchmarker(Text pFunction)
		: mFunction{pFunction}
	{
		const TimePoint currentTimePoint = Clock::now();
		mStart = (u64)std::chrono::duration_cast<std::chrono::microseconds>(currentTimePoint - sAppStartTimePoint).count();
	}

	INTERNAL_FunctionBenchmarker::~INTERNAL_FunctionBenchmarker()
	{
		const TimePoint currentTimePoint = Clock::now();
		const u64 end = (u64)std::chrono::duration_cast<std::chrono::microseconds>(currentTimePoint - sAppStartTimePoint).count();

		printf("%lluus:\t\t\t%s\n", end - mStart, mFunction);
	}

#endif

}