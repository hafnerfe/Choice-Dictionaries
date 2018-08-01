/*
*	Header defines the types _t::entry_t and _t::len_t
*
*	Created by Felix Hafner, 29.05.18
*/

#include <cstdint>

#ifndef TYPES_H
#define TYPES_H

namespace _t {
	//typedef __uint128_t entry_t;		// b=64
	typedef uint64_t entry_t;			// b=32
	typedef uint64_t len_t;

}

#endif
