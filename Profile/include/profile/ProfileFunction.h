#pragma once

#include <stdint.h>
#include <limits.h>

namespace profile
{
	static const uint64_t kUndefinedFunctionID = LLONG_MAX;

	/// @class ProfileFunction
	/// @brief Registers a function, for a thread, with the profiler
	class ProfileFunction
	{
	public:
		ProfileFunction(uint64_t& id, const char* label);

		/// @brief Get the unique ID for this function (in the current thread)
		uint64_t getID() const;

	private:
		uint64_t& id;
	};
}
