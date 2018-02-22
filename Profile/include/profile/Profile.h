#pragma once

#include "profile/ProfileCore.h"
#include "profile/ProfileSwitch.h"
#include "profile/ProfileEvent.h"

#include <thread>
#include <stdint.h>

#ifdef PROFILE_ENABLED

# define PROFILE_INIT()	\
		::profile::init()

# define PROFILE_THREAD(__label)																		\
		static PROFILE_THREAD_LOCAL uint64_t __thread_id = ::profile::kUndefinedThreadID;				\
		::profile::ProfileThread __profileThread(__thread_id, __label);									\
		PROFILE_SCOPE(__label)

# define PROFILE_FUNCTION()																				\
		static PROFILE_THREAD_LOCAL uint64_t __profile_function_id = ::profile::kUndefinedFunctionID;	\
		::profile::ProfileFunction __profileFunction(__profile_function_id, __FUNCSIG__);				\
		::profile::ProfileSample __profileSample(__profileFunction);

# define PROFILE_SCOPE(__label)																			\
		static PROFILE_THREAD_LOCAL uint64_t __profile_scope_id = ::profile::kUndefinedFunctionID;		\
		::profile::ProfileFunction __profileScope(__profile_scope_id, __label);							\
		::profile::ProfileSample __profileSample(__profileScope);

# define PROFILE_EVENT(__label)																			\
		static PROFILE_THREAD_LOCAL uint64_t __profile_event_id = ::profile::kUndefinedEventID;			\
		::profile::ProfileEvent __profileEvent(__profile_event_id, __label);							\
		::profile::emitEvent(__profileEvent);

#else

# define PROFILE_INIT()
# define PROFILE_THREAD(_label)
# define PROFILE_FUNCTION() 
# define PROFILE_SCOPE(_label)
# define PROFILE_EVENT(_label)

#endif
