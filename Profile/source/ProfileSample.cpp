#include "profile/ProfileSample.h"
#include "profile/Profile.h"

namespace profile
{
	ProfileSample::ProfileSample(const ProfileFunction& inProfileFunction) : profileFunction(inProfileFunction)
	{
		::profile::startSample(profileFunction);
	}

	ProfileSample::~ProfileSample()
	{
		::profile::finishSample(profileFunction);
	}
}
