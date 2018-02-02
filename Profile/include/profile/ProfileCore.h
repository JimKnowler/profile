#pragma once

#include "profile/ProfileSample.h"
#include "profile/ProfileFunction.h"
#include "profile/ProfileThread.h"
#include "profile/ProfileThreadLocal.h"

namespace profile
{
	/// @brief Initialize the profiler
	/// @note invoked by PROFILE_INIT()
	void init();

	/// @brief register a thread with the profiler
	/// @return unique ID for this thread
	/// @note invoked by PROFILE_THREAD()
	uint64_t registerThread(const char* threadName);

	/// @brief register a function with the current thread
	/// @return unique ID for this function in this thread
	/// @note invoked by PROFILE_FUNCTION()
	uint64_t registerFunction(const char* functionName);

	/// @brief start a sample of a function in the current thread
	/// @note invoked by PROFILE_FUNCTION()
	void startSample(const ::profile::ProfileFunction& function);

	/// @brief finish a sample of a function in the current thread
	/// @note invoked by PROFILE_FUNCTION()
	void finishSample(const ::profile::ProfileFunction& function);
}
