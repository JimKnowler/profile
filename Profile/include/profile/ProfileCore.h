#pragma once

#include "profile/ProfileSample.h"
#include "profile/ProfileFunction.h"
#include "profile/ProfileThread.h"
#include "profile/ProfileThreadLocal.h"
#include "profile/ProfileEvent.h"
#include "profile/ProfileCounter.h"

namespace profile
{
	/// @brief Initialize the profiler
	/// @note invoked by PROFILE_INIT()
	void init();

	/// @brief register a thread with the profiler
	/// @return unique ID for this thread
	/// @note invoked by PROFILE_THREAD()
	uint64_t registerThread(const char* threadLabel);

	/// @brief register a function with the current thread
	/// @return unique ID for this function in this thread
	/// @note invoked by PROFILE_FUNCTION() / PROFILE_SCOPE()
	uint64_t registerFunction(const char* functionLabel);

	/// @brief start a sample of a function in the current thread
	/// @note invoked by PROFILE_FUNCTION() / PROFILE_SCOPE()
	void startSample(const ::profile::ProfileFunction& function);

	/// @brief finish a sample of a function in the current thread
	/// @note invoked by PROFILE_FUNCTION() / PROFILE_SCOPE()
	void finishSample(const ::profile::ProfileFunction& function);

	/// @brief register an Event with the current thread
	/// @return unique ID for this Event in this thread
	/// @note invoked by PROFILE_EVENT()
	uint64_t registerEvent(const char* eventLabel);

	/// @brief Emit an event at the current time
	/// @note invoked by PROFILE_EVENT()
	void emitEvent(const ::profile::ProfileEvent& event);

	/// @brief register a counter
	/// @return unique ID for this counter
	/// @note invoked by PROFILE_COUNTER()
	uint64_t registerCounter(const char* counterLabel);

	/// @brief Emit a value for a counter
	/// @note invoked by PROFILE_COUNTER_SET() / PROFILE_COUNTER_INC() / PROFILE_COUNTER_DEC()
	void emitCounter(const ::profile::ProfileCounter& counter);
}
