#include "profile/ProfileCounter.h"
#include "profile/ProfileCore.h"

namespace profile
{


	ProfileCounter::ProfileCounter(const char* label)
	{
		id = ::profile::registerCounter(label);
		value = 0;
	}

	ProfileCounter::~ProfileCounter()
	{

	}

	uint64_t ProfileCounter::getID() const
	{
		return id;
	}

	int ProfileCounter::getValue() const
	{
		return value;
	}

	void ProfileCounter::operator=(int inValue)
	{
		value = inValue;
		
		::profile::emitCounter(*this);
	}
	
	void ProfileCounter::operator-=(int inValue)
	{
		*this = (value - inValue);
	}

	void ProfileCounter::operator+=(int inValue)
	{
		*this = (value + inValue);
	}

}