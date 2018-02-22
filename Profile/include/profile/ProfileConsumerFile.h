#pragma once

#include "profile/IProfileConsumer.h"

#include <mutex>
#include <fstream>

namespace profile
{
	/// @class ProfileConsumerFile
	/// @brief Concrete Implementation of IProfileConsumer that writes to a text file
	class ProfileConsumerFile : public IProfileConsumer
	{
	public:
		ProfileConsumerFile(const char* filename);
		~ProfileConsumerFile();

	public: // IProfileConsumer
		void onProfileRegisterThread(uint64_t threadID, const char* threadLabel) override;
		void onProfileRegisterFunction(uint64_t threadID, uint64_t functionID, const char* functionLabel) override;
		void onProfileStartSample(uint64_t threadID, uint64_t functionID, uint64_t time) override;
		void onProfileFinishSample(uint64_t threadID, uint64_t functionID, uint64_t time) override;
		void onProfileRegisterEvent(uint64_t threadID, uint64_t eventID, const char* eventLabel) override;
		void onProfileEmitEvent(uint64_t threadID, uint64_t eventID, uint64_t time) override;
		void onProfileRegisterCounter(uint64_t counterID, const char* counterLabel) override;
		void onProfileEmitCounterValue(uint64_t counterID, int value) override;

	private:
		std::mutex mutex;
		std::ofstream file;
	};
}

