// ProfileSampleApp.cpp : Defines the entry point for the console application.
//

#include "profile/Profile.h"

#include <cstdio>
#include <cstdlib>

#include <memory>
#include <mutex>
#include <random>
#include <thread>

void runTest();
void mockFunction(int milliseconds, int callDepth);
void workerThreadEntry(int threadIndex, const std::string& threadLabel);
void counterThreadEntry(int threadIndex, const std::string& threadLabel);
int getRandomNumber(int range);
std::string createWorkerThreadName(int threadIndex);
std::string createCounterThreadName(int threadIndex);

const int kTestDurationMilliseconds = 5 * 1000;
const int kNumThreads = 10;
const int kNumCounters = 2;
const int kMaxCallDepth = 20;

PROFILE_COUNTER(myProfileCounter);
PROFILE_COUNTER(myProfileCounter2);

struct WorkerThread {
	std::thread thread;
	std::string threadLabel;
};

struct CounterThread {
	std::thread thread;
	std::string threadLabel;
};

int main(int argc, const char* argv[])
{
	PROFILE_INIT();
	PROFILE_THREAD("main");
	
	PROFILE_COUNTER_INIT(myProfileCounter, "my profile counter");
	PROFILE_COUNTER_INIT(myProfileCounter2, "my profile counter 2");

	runTest();

	return 0;
}

void runTest() {
	PROFILE_FUNCTION();
	
	WorkerThread workerThreads[kNumThreads];
	CounterThread counterThreads[kNumCounters];

	{
		PROFILE_SCOPE("start threads");

		for (int i = 0; i < kNumThreads; i++) {
			WorkerThread& workerThread = workerThreads[i];
			workerThread.threadLabel = createWorkerThreadName(i);
			workerThread.thread = std::thread(workerThreadEntry, i, workerThread.threadLabel);
		}

		for (int i = 0; i < kNumCounters; i++) {
			CounterThread& counterThread = counterThreads[i];
			counterThread.threadLabel = createCounterThreadName(i);
			counterThread.thread = std::thread(counterThreadEntry, i, counterThread.threadLabel);
		}
	}


	{
		PROFILE_SCOPE("waiting to join threads");

		for (int i = 0; i < kNumThreads; i++) {
			workerThreads[i].thread.join();
		}

		for (int i = 0; i < kNumCounters; i++) {
			counterThreads[i].thread.join();
		}
	}
}

void workerThreadEntry(int threadIndex, const std::string& threadLabel) {
	PROFILE_THREAD(threadLabel.c_str());

	mockFunction(kTestDurationMilliseconds, kMaxCallDepth);
}

void mockFunction(int milliseconds, int callDepth) {
	PROFILE_FUNCTION();
	
	if ( (callDepth > 0) && (milliseconds > 1) ) {
		int remaining = milliseconds;

		while (remaining > 0) {
			int duration;
			
			duration = getRandomNumber(remaining / 64);
			std::this_thread::sleep_for(std::chrono::milliseconds(duration));
			remaining -= duration;

			if (remaining > 0) {
				duration = getRandomNumber(remaining / 16);
				mockFunction(duration, callDepth - 1);
				remaining -= duration;
			}

			int randomNumber = getRandomNumber(1000);
			if (1 == randomNumber) {
				PROFILE_EVENT("A Test Event");
			}

			if (remaining > 0) {
				duration = getRandomNumber(remaining / 64);
				std::this_thread::sleep_for(std::chrono::milliseconds(duration));
				remaining -= duration;
			}
		}
	}
	else {
		// just sleep for the duration of the call :)
		std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
	}
}

void counterThreadEntry(int threadIndex, const std::string& threadLabel) {
	PROFILE_THREAD(threadLabel.c_str());

	if (threadIndex == 0) {
		PROFILE_COUNTER_SET(myProfileCounter, 12);
	} else {
		PROFILE_COUNTER_SET(myProfileCounter2, 38);
	}

	int milliseconds = kTestDurationMilliseconds;

	while (milliseconds > 0) {
		int duration = getRandomNumber(32);
		std::this_thread::sleep_for(std::chrono::milliseconds(duration));

		int direction = getRandomNumber(3);
		int value = getRandomNumber(3);
		if (direction == 1) {
			if (threadIndex == 0) {
				PROFILE_COUNTER_DEC(myProfileCounter, value);
			}
			else {
				PROFILE_COUNTER_DEC(myProfileCounter2, value);
			}
		}
		else if (direction == 2) {
			if (threadIndex == 0) {
				PROFILE_COUNTER_INC(myProfileCounter, value);
			}
			else {
				PROFILE_COUNTER_INC(myProfileCounter2, value);
			}
		}

		milliseconds -= duration;
	}
}

/// @return random value in [1..range]
int getRandomNumber(int range) {
	PROFILE_FUNCTION();

	if (range <= 1) {
		return 1;
	}

	static std::mutex mutex;
	{
		PROFILE_SCOPE("mutex acquired");

		std::lock_guard<std::mutex> autoLock(mutex);

#if 0 
		return (std::rand() % range) + 1;
#else
		static std::default_random_engine e{};
		std::uniform_int_distribution<int> d{ 1, range };
		return d(e);
	}
#endif
}

std::string createWorkerThreadName(int threadIndex) {
	char bufferName[32];
	sprintf_s(bufferName, "Worker Thread #%d", threadIndex + 1);	
	std::string strName = bufferName;
	return strName;
}

std::string createCounterThreadName(int threadIndex) {
	char bufferName[32];
	sprintf_s(bufferName, "Counter Thread #%d", threadIndex + 1);
	std::string strName = bufferName;
	return strName;
}