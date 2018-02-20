// ProfileSampleApp.cpp : Defines the entry point for the console application.
//

#include "profile/Profile.h"

#include <cstdio>
#include <cstdlib>

#include <memory>
#include <mutex>
#include <random>

void runTest();
void mockFunction(int milliseconds, int callDepth);
void workerThreadEntry(int threadIndex, const std::string& threadLabel);
int getRandomNumber(int range);
std::string createWorkerThreadName(int threadIndex);

const int kTestDurationMilliseconds = 20 * 1000;
const int kNumThreads = 10;
const int kMaxCallDepth = 20;

int main(int argc, const char* argv[])
{
	PROFILE_INIT();
	PROFILE_THREAD("main");

	runTest();

	return 0;
}

void runTest() {
	PROFILE_FUNCTION();

	struct WorkerThread {
		std::thread thread;
		std::string threadLabel;
	};

	WorkerThread threads[kNumThreads];

	{
		PROFILE_SCOPE("start threads");

		for (int i = 0; i < kNumThreads; i++) {
			WorkerThread& workerThread = threads[i];
			workerThread.threadLabel = createWorkerThreadName(i);
			workerThread.thread = std::thread(workerThreadEntry, i, workerThread.threadLabel);
		}
	}

	{
		PROFILE_SCOPE("waiting to join threads");

		for (int i = 0; i < kNumThreads; i++) {
			threads[i].thread.join();
		}
	}
}

void workerThreadEntry(int threadIndex, const std::string& threadName) {	
	PROFILE_THREAD(threadName.c_str());

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

/// @return random value in [1..range]
int getRandomNumber(int range) {
	PROFILE_FUNCTION();

	static std::mutex mutex;
	{
		PROFILE_SCOPE("mutex acquired");

		std::lock_guard<std::mutex> autoLock(mutex);

#if 0 
		return (std::rand() % range) + 1;
#else
		static std::default_random_engine e{};
		static std::uniform_int_distribution<int> d{ 1, range };
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