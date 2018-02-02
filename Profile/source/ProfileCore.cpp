#include "profile/ProfileCore.h"
#include "profile/IProfileConsumer.h"
#include "profile/ProfileConsumerFile.h"
#include "profile/ProfileConsumerNull.h"
#include "profile/ProfileTimer.h"

#include <memory>

namespace profile
{
	
	namespace
	{
		uint64_t threadCount = 0;								/// @brief used to issue unique ID to each thread
		std::mutex mutexThreadCounter;							/// @brief used to ensure thread-safe access to threadCount

		PROFILE_THREAD_LOCAL uint64_t threadID;					/// @brief unique ID for the current thread

		PROFILE_THREAD_LOCAL uint64_t functionCounter;			/// @brief used to issue unique ID to each function in a thread

		std::unique_ptr<IProfileConsumer> profileConsumer = std::unique_ptr<IProfileConsumer>(new ProfileConsumerNull());

		ProfileTimer timer;
	}

	void init()
	{
		profileConsumer = std::unique_ptr<IProfileConsumer>(new ProfileConsumerFile("profile.txt"));
		timer.start();
	}

	uint64_t registerThread(const char* threadLabel)
	{
		{
			std::lock_guard<std::mutex> autoLock(mutexThreadCounter);
			threadID = threadCount++;
		}

		profileConsumer->onProfileRegisterThread(threadID, threadLabel);

		functionCounter = 0;

		return threadID;
	}

	uint64_t registerFunction(const char* functionLabel)
	{
		uint64_t functionID = functionCounter++;

		profileConsumer->onProfileRegisterFunction(threadID, functionID, functionLabel);

		return functionID;
	}

	void startSample(const ProfileFunction& function)
	{
		uint64_t functionID = function.getID();

		uint64_t time = timer.getElapsedMicroseconds();
		
		profileConsumer->onProfileStartSample(threadID, functionID, time);
	}

	void finishSample(const ProfileFunction& function)
	{
		uint64_t functionID = function.getID();

		uint64_t time = timer.getElapsedMicroseconds();

		profileConsumer->onProfileFinishSample(threadID, functionID, time);
	}
}
