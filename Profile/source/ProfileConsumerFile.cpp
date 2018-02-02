#include "profile/ProfileConsumerFile.h"

namespace profile
{
	ProfileConsumerFile::ProfileConsumerFile(const char* filename)
	{
		file.open(filename, std::ios::out);
	}

	ProfileConsumerFile::~ProfileConsumerFile()
	{
	}

	void ProfileConsumerFile::onProfileRegisterThread(uint64_t threadID, const char* threadLabel)
	{
		std::lock_guard<std::mutex> autoLock(mutex);

		file << "T " << threadID << " " << threadLabel << "\n";		
	}

	void ProfileConsumerFile::onProfileRegisterFunction(uint64_t threadID, uint64_t functionID, const char* functionLabel)
	{
		std::lock_guard<std::mutex> autoLock(mutex);

		file << "F " << threadID << " " << functionID << " " << functionLabel << "\n";
	}

	void ProfileConsumerFile::onProfileStartSample(uint64_t threadID, uint64_t functionID, uint64_t time)
	{
		std::lock_guard<std::mutex> autoLock(mutex);

		file << "S " << threadID << " " << functionID << " " << time << "\n";
	}

	void ProfileConsumerFile::onProfileFinishSample(uint64_t threadID, uint64_t functionID, uint64_t time)
	{
		std::lock_guard<std::mutex> autoLock(mutex);

		file << "E " << threadID << " " << functionID << " " << time << "\n";
	}
}
