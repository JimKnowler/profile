#include "profile/ProfileTimer.h"

namespace profile
{
	/// @note Using QueryPerformanceCounter() due to reported issues with
	///       accuracy of std::chrono in VS2013

	ProfileTimer::ProfileTimer()
	{
		QueryPerformanceFrequency(&frequency);
		QueryPerformanceCounter(&startTime);
	}

	bool ProfileTimer::start()
	{
		QueryPerformanceCounter(&startTime);
		return true;
	}

	uint64_t ProfileTimer::getStartTime()
	{
		int64_t time = int64_t(startTime.QuadPart);
		return static_cast<uint64_t>(time);
	}

	float ProfileTimer::getElapsedTime()
	{
		LARGE_INTEGER endTime;
		QueryPerformanceCounter(&endTime);

		float elapsedTime = float(endTime.QuadPart - startTime.QuadPart);
		elapsedTime /= float(frequency.QuadPart);

		return elapsedTime;
	}

	uint64_t ProfileTimer::getElapsedMicroseconds()
	{
		LARGE_INTEGER endTime;
		QueryPerformanceCounter(&endTime);

		int64_t elapsedTime = endTime.QuadPart - startTime.QuadPart;
		return static_cast<uint64_t>(elapsedTime);
	}
}
