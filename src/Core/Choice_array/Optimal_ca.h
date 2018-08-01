/*
*	This is the Interface for an Optimal Choice Array
*	This Datastructure supports all Operations (initialization, read, write, nonzero) in constant time.
*
*	Created by Felix Hafner, 18.06.18
*/

#ifndef OPTIMAL_CA_H
#define OPTIMAL_CA_H

#include "Choice_array.h"
#include <cstdint>

template <class T>
class Optimal_ca : public Choice_array<T> {
		T *a;								// No smart pointer because of Performance.
		_ca_len_t k;						// k conceptually seperates the array.
		_ca_len_t n;						// The size of the Choice array.

		// Helper Functions:
		_ca_len_t mate(_ca_len_t i) const;
		void simple_write(_ca_len_t i, T x);

	public:

		// Constructor:
		Optimal_ca(_ca_len_t size);

		// Destructor:
		~Optimal_ca();

		// Operations:
		T read(_ca_len_t i) override;
		_ca_len_t nonzero() override;
		void write(_ca_len_t i, T x) override;

};

// include source file, because of the way C++ handles templates
#include "Optimal_ca.cpp"

#endif //OPTIMAL_CA_H