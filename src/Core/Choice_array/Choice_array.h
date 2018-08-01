/*
*	Defines an Interface for the operations of a Choice Array (read, write, nonzero)
*
*	Created by Felix Hafner, 29.05.18
*/

#ifndef CHOICE_ARRAY_H
#define CHOICE_ARRAY_H

#include <cstdint>

typedef uint64_t _ca_len_t;		// Defines the data type that stores the length of the CA.

template <class T>
class Choice_array{
	public:
		virtual ~Choice_array() = default;
		virtual T read(_ca_len_t) = 0;
		virtual _ca_len_t nonzero() = 0;
		virtual void write(uint64_t i, T x) = 0;
};

#endif //CHOICE_ARRAY_H
