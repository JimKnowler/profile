#pragma once

#include <stdint.h>

namespace profile
{
	class ProfileCounter
	{
	public:
		ProfileCounter(const char* label);
		~ProfileCounter();
		
		/// @brief Set the counter to a specific counter
		void operator=(int value);
		
		/// @brief Increment the counter
		void operator+=(int value);

		/// @brief Decrement the counter
		void operator-=(int value);

		/// @brief get the unique ID for this counter
		uint64_t getID() const;

		/// @brief get the current value of this counter
		int getValue() const;

	private:
		// make non-copyable
		ProfileCounter(const ProfileCounter&) = delete;
		ProfileCounter& operator=(const ProfileCounter&) = delete;

		uint64_t id;
		int value;
	};

}
