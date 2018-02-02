#pragma once

#include "profile/ProfileFunction.h"

namespace profile
{
	/// @class ProfileSample
	/// @brief Notifies the profiler that sample has begun when it comes in scope, and notifies the 
	///        profiler that the sample has finished when it goes out of scope
	class ProfileSample
	{
	public:
		/// @brief Constructor - notifies the profiler that a sample is beginning for the specified function
		ProfileSample(const ProfileFunction& profileFunction);

		/// @brief Destructor - notifies the profiler that this sample has finished
		~ProfileSample();

	private:
		const ProfileFunction& profileFunction;
	};
}
