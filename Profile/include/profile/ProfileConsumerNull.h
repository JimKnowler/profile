#pragma once

#include "profile/IProfileConsumer.h"

namespace profile
{
	/// @class ProfileConsumerNull
	/// @brief Null implementation of IProfilerConsumer
	class ProfileConsumerNull : public IProfileConsumer
	{
	public: // IProfileConsumer
		virtual void onProfileRegisterThread(uint64_t threadID, const char* threadLabel);
		virtual void onProfileRegisterFunction(uint64_t threadID, uint64_t functionID, const char* functionLabel);
		virtual void onProfileStartSample(uint64_t threadID, uint64_t functionID, uint64_t time);
		virtual void onProfileFinishSample(uint64_t threadID, uint64_t functionID, uint64_t time);
	};
}
