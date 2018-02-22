#pragma once

#include <stdint.h>
#include <limits.h>

namespace profile
{
	static const uint64_t kUndefinedEventID = LLONG_MAX;

	/// @class ProfileEvent
	/// @brief Registers an event, for a thread, with the profiler
	class ProfileEvent
	{
	public:
		ProfileEvent(uint64_t& id, const char* label);

		/// @brief Get the unique ID for this Event (in the current thread)
		uint64_t getID() const;

	private:
		uint64_t& id;
	};
}
