#pragma once

#include <stdint.h>
#include <windows.h>

namespace profile
{
	/// @class ProfileTimer
	/// @brief Measure elapsed time with a high resolution timer (microseconds)
	/// @todo Replace with std::chrono timing 
	/// @note Visual Studio 2013 has a broken implementation of chrono for high resolution time measurement
	class ProfileTimer
	{
	public:
		/// @brief Constructor
		/// @note Automatically starts the timer
		ProfileTimer();

		/// @brief Start the timer
		bool start();

		/// @brief Get the time when the timer was last started (as microseconds)
		uint64_t getStartTime();

		/// @brief Get the time elapsed since timer was (last) started (in seconds)
		float getElapsedTime();

		/// @brief Get the time elapsed since the timer was (last) started (in microseconds)
		uint64_t getElapsedMicroseconds();

	private:
		LARGE_INTEGER frequency;
		LARGE_INTEGER startTime;
	};
}
