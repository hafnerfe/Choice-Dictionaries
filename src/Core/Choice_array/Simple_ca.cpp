/*
*	This is the implementation of the Simple_ca.h
*
*	Created by Felix Hafner, 29.05.18
*/


#include <cstdint>
#include <cstdlib>


template <class T>
T Simple_ca::read(_ca_len_t i) {
	return entries[i-1];
}


template <class T>
_ca_len_t Simple_ca::nonzero() {
	for (_ca_len_t i = 0; i < n; ++i) {
		if (entries[i])
			return i+1;
	}
	return 0;
}


template <class T>
void Simple_ca::write(_ca_len_t i, T x) {
	entries[i-1] = x;
}


// Constructor:
template <class T>
Simple_ca::Simple_ca(_ca_len_t size): n(size) {
	// Allocate memory for the entries:
	entries = (T *) calloc(size, sizeof(T));
	if (entries==nullptr)
		exit(EXIT_FAILURE);
}


// Destructor:
template <class T>
Simple_ca::~Simple_ca() {
	if (entries)
		free(entries);
	entries = nullptr;
}
