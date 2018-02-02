#pragma once

#include <stdint.h>
#include <limits.h>

namespace profile
{
	static const uint64_t kUndefinedThreadID = LLONG_MAX;

	/// @class ProfileThread
	/// @brief Registers a Thread with the profiler
	class ProfileThread
	{
	public:
		ProfileThread(uint64_t& id, const char* label);

		/// @brief Get the unique ID for this thread
		uint64_t getID() const;

	private:
		uint64_t& id;
	};
}
