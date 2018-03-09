#include "profile/ProfileCore.h"
#include "profile/IProfileConsumer.h"
#include "profile/ProfileConsumerFile.h"
#include "profile/ProfileConsumerNull.h"
#include "profile/ProfileTimer.h"

#include <memory>
#include <atomic>

namespace profile
{
	
	namespace
	{
		std::atomic<uint64_t> threadCount = 0;					/// @brief used to issue unique ID to each thread
		PROFILE_THREAD_LOCAL uint64_t threadID;					/// @brief unique ID for the current thread

		PROFILE_THREAD_LOCAL uint64_t functionCounter;			/// @brief used to issue unique ID to each function in a thread
		PROFILE_THREAD_LOCAL uint64_t eventCounter;				/// @brief used to issue unique ID to each event in a thread

		std::unique_ptr<IProfileConsumer> profileConsumer = std::unique_ptr<IProfileConsumer>(new ProfileConsumerNull());

		ProfileTimer timer;

		std::atomic<uint64_t> counterCount = 0;
	}

	void init()
	{
		profileConsumer = std::unique_ptr<IProfileConsumer>(new ProfileConsumerFile("profile.txt"));
		timer.start();
	}

	uint64_t registerThread(const char* threadLabel)
	{
		threadID = threadCount.fetch_add(1);

		profileConsumer->onProfileRegisterThread(threadID, threadLabel);

		functionCounter = 0;
		eventCounter = 0;

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

	uint64_t registerEvent(const char* eventLabel)
	{
		uint64_t eventID = eventCounter++;

		profileConsumer->onProfileRegisterEvent(threadID, eventID, eventLabel);

		return eventID;
	}

	void emitEvent(const ProfileEvent& event)
	{
		uint64_t eventID = event.getID();

		uint64_t time = timer.getElapsedMicroseconds();

		profileConsumer->onProfileEmitEvent(threadID, eventID, time);
	}

	uint64_t registerCounter(const char* counterLabel)
	{
		uint64_t counterID = counterCount.fetch_add(1);

		profileConsumer->onProfileRegisterCounter(counterID, counterLabel);
		
		return counterID;
	}

	void emitCounter(const ProfileCounter& counter)
	{
		uint64_t counterID = counter.getID();

		uint64_t time = timer.getElapsedMicroseconds();
		int value = counter.getValue();

		profileConsumer->onProfileEmitCounterValue(counterID, time, value);
	}

}
