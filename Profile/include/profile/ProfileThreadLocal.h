#pragma once

/// @note Visual Studio 2013 does not support C++11 thread_local
#define PROFILE_THREAD_LOCAL __declspec( thread )
