#include "profile/ProfileTimer.h"

namespace profile
{
	/// @note Using QueryPerformanceCounter() due to reported issues with
	///       accuracy of std::chrono in VS2013

	ProfileTimer::ProfileTimer()
	{
		start();
	}

	bool ProfileTimer::start()
	{
		startTime = clock.now();
		return true;
	}

	uint64_t ProfileTimer::getElapsedMicroseconds()
	{
		using namespace std::chrono;
		
		TimePointType now = clock.now();

		auto elapsed = now - startTime;
		auto elapsedMicroseconds = duration_cast<microseconds>(elapsed);

		return elapsedMicroseconds.count();
	}
}
