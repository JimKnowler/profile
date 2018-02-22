#include "profile/ProfileEvent.h"
#include "profile/ProfileCore.h"

namespace profile
{
	ProfileEvent::ProfileEvent(uint64_t& inID, const char* label) : id(inID)
	{
		if (id == kUndefinedEventID)
		{
			id = ::profile::registerEvent(label);
		}
	}

	uint64_t ProfileEvent::getID() const
	{
		return id;
	}

}
