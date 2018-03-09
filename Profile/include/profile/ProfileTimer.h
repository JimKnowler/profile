#pragma once

#include <chrono>

namespace profile
{
	/// @class ProfileTimer
	/// @brief Measure elapsed time with a high resolution timer (microseconds)
	class ProfileTimer
	{
	public:
		/// @brief Constructor
		/// @note Automatically starts the timer
		ProfileTimer();

		/// @brief Start the timer
		bool start();

		/// @brief Get the time elapsed since the timer was (last) started (in microseconds)
		uint64_t getElapsedMicroseconds();

	private:
		using ClockType = std::chrono::steady_clock;
		using TimePointType = std::chrono::time_point<ClockType>;

		ClockType clock;
		TimePointType startTime;
	};
}
