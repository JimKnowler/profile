#include "profile/ProfileConsumerNull.h"

namespace profile
{
	void ProfileConsumerNull::onProfileRegisterThread(uint64_t threadID, const char* threadLabel)
	{
	}

	void ProfileConsumerNull::onProfileRegisterFunction(uint64_t threadID, uint64_t functionID, const char* functionLabel)
	{
	}

	void ProfileConsumerNull::onProfileStartSample(uint64_t threadID, uint64_t functionID, uint64_t time)
	{
	}

	void ProfileConsumerNull::onProfileFinishSample(uint64_t threadID, uint64_t functionID, uint64_t time)
	{
	}

	void ProfileConsumerNull::onProfileRegisterEvent(uint64_t threadID, uint64_t eventID, const char* eventLabel)
	{
	}

	void ProfileConsumerNull::onProfileEmitEvent(uint64_t threadID, uint64_t eventID, uint64_t time)
	{
	}
}
