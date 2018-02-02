#pragma once

#include <stdint.h>

namespace profile
{
	/// @class IProfileConsumer
	/// @brief Interface for consuming profiler output
	/// @note See ProfileConsumerFile for an example of implementing a profile consumer
	class IProfileConsumer
	{
	public:
		virtual ~IProfileConsumer() {}

		/// @brief Register a thread
		virtual void onProfileRegisterThread(uint64_t threadID, const char* threadLabel) = 0;

		/// @brief Register a function for a thread
		virtual void onProfileRegisterFunction(uint64_t threadID, uint64_t functionID, const char* functionLabel) = 0;

		/// @brief Start a sample of a function
		virtual void onProfileStartSample(uint64_t threadID, uint64_t functionID, uint64_t time) = 0;

		/// @brief Finish a sample of a function
		virtual void onProfileFinishSample(uint64_t threadID, uint64_t functionID, uint64_t time) = 0;
	};
}
