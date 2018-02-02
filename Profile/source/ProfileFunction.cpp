#include "profile/ProfileFunction.h"
#include "profile/Profile.h"

namespace profile
{
	ProfileFunction::ProfileFunction(uint64_t& inID, const char* label) : id(inID)
	{
		if (id == kUndefinedFunctionID)
		{
			id = ::profile::registerFunction(label);
		}
	}

	uint64_t ProfileFunction::getID() const
	{
		return id;
	}
}
