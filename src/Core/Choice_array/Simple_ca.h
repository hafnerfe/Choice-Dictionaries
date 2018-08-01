/*
*	This is a simple Choice Array, i.e. the simplest version one can think of.
*	It simply stores the entries in an array and searches for an entry when nonzero is called.
*
*	Created by Felix Hafner, 29.05.18
*/

#ifndef SIMPLE_CA_H
#define SIMPLE_CA_H

#include "Choice_array.h"
#include <cstdint>

template <class T>
class Simple_ca : public Choice_array {

		T *entries;
		_ca_len_t n;

	public:

		Simple_ca(_ca_len_t size);
		~Simple_ca();
		
		T read(_ca_len_t i) override;
		_ca_len_t nonzero() override;
		void write(_ca_len_t i, T x) override;
};

// Include source file because of the way C++ handles templates
#include "Simple_ca.cpp"

#endif //SIMPLE_CA_H
