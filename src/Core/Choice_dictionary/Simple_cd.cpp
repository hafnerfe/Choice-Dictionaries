/*
*	Source code for the interface Simple_cd.h
*	Stores entries as expected.
*	Is basically an optimal_cd using a simple_ca! May be changed later.
*
*	Created by Felix Hafner, 29.05.18
*/

#include "Simple_cd.h"
#include "Core/Utilities/Bit_operations.h"
#include <cstdlib>

// Constructor
Simple_cd::Simple_cd(_t::len_t n): 
		universe_size(n),
		s(nullptr), 
		size_s((n/WORD_LEN)+((n%WORD_LEN)==0?0:1)){
	s = (_t::len_t*) calloc(size_s,sizeof(_t::len_t));
	if (s==nullptr)
		exit(EXIT_FAILURE);
}

// Deconstructor
Simple_cd::~Simple_cd() { 
	if (s)
		free(s); 
	s = nullptr;
}


_t::len_t Simple_cd::choice() {
	for (_t::len_t i = 0; i < size_s; ++i) {
		if (!s[i]) continue;
		return find_one(s[i])+ WORD_LEN*i;
	}
	return 0;
}


bool Simple_cd::contains(_t::len_t l) {
	return (s[(l-1)/WORD_LEN]) & ((_t::len_t)1<<((l%(WORD_LEN))-1));
}


void Simple_cd::insert(_t::len_t l) {
	s[(l-1)/WORD_LEN] |= ((_t::len_t)1 << ((l%WORD_LEN)-1));
}


void Simple_cd::del(_t::len_t l) {
	s[(l-1)/WORD_LEN] &= ~((_t::len_t)1 << ((l%WORD_LEN)-1));
}


// -----------------------------------------
// Operations needed for profiling. May also be changed later.

void Simple_cd::init(_t::len_t n) {
	destroy();
	universe_size=n;
	size_s = (n/WORD_LEN)+((n%WORD_LEN)==0?0:1);
	s = (_t::len_t*) calloc(size_s,sizeof(_t::len_t));
	if (s==nullptr)
		exit(EXIT_FAILURE);
}

void Simple_cd::destroy(){
	if (s)
		free(s);
	s = nullptr;
}


