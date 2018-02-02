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
		virtual void onProfileRegisterThread(uint64_t threadID, const char* threadLabel);
		virtual void onProfileRegisterFunction(uint64_t threadID, uint64_t functionID, const char* functionLabel);
		virtual void onProfileStartSample(uint64_t threadID, uint64_t functionID, uint64_t time);
		virtual void onProfileFinishSample(uint64_t threadID, uint64_t functionID, uint64_t time);

	private:
		std::mutex mutex;
		std::ofstream file;
	};
}

