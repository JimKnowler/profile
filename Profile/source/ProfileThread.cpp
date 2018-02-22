#include "profile/ProfileThread.h"
#include "profile/ProfileCore.h"

namespace profile
{
	ProfileThread::ProfileThread(uint64_t& inID, const char* label) : id(inID)
	{
		if (id == kUndefinedFunctionID)
		{
			id = ::profile::registerThread(label);
		}
	}

	uint64_t ProfileThread::getID() const
	{
		return id;
	}
}
