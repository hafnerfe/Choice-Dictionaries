/*
*	Bit operations without templates.
*	Mainly contains specializations.
*
*	Created by Felix Hafner, 19.07.18
*/

#include "Bit_operations.h"


#ifdef __GNUC__

// GCC has a very efficient find_one implementation.
// Always returns position of least significant one.
template<>
uint16_t find_one<uint64_t>(uint64_t x) {return __builtin_ffsll(x); }

// Reduce Problem from 128 to 64 Bits.
template<>
uint16_t find_one<__uint128_t>(__uint128_t x) {
	uint64_t lower = (uint64_t) x;
	if (lower)
		return __builtin_ffsll(lower);
	uint64_t upper = (uint64_t) (x >> 64);
	return 64+__builtin_ffsll(upper);
}

#endif


