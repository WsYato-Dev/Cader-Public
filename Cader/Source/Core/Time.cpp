#include "Cader/Core/Time.h"

#include <chrono>
#include <thread>

namespace CDR {

	using Clock = std::chrono::steady_clock;
	using TimePoint = Clock::time_point;

	static TimePoint sAppStartTimePoint;
	static TimePoint sLastTickTimePoint;

	Milliseconds Time::sNow = 0;
	float Time::sDelta = 0.0f;

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

		// Temporary. This is to limit the cpu usage.
		// This is also to get the correct delta for now. If the fps is higher than 1000, the delta will be 0 because it is milliseconds. Using microseconds will be very inefficient.
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}