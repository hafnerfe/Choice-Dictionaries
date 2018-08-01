/*
*	This is the source file for the Interface "Bit_operations.h"
*	Header is not included because of template functions.
*	For more information see e.g. https://stackoverflow.com/questions/3040480/c-template-function-compiles-in-header-but-not-implementation
*	.tpp because this file contains template implementations.
*
*	Created by Felix Hafner, 15.06.18
*/

#ifndef BIT_OPERATIONS_CPP
#define BIT_OPERATIONS_CPP


#include <iostream>
using namespace std;

template<class T>
uint16_t find_one(T x) {
	/*
	*	Returns the position of an arbitrary set bit in x. 0, if x==0.
	*/
	// Loop unrolling:
	for (uint16_t i = 0; i < sizeof(T)*8;i+=8) {
    if (((T)1 << (i)) & x)
      return i+1;
    if (((T)1 << (i+1)) & x)
      return i+2;
    if (((T)1 << (i+2)) & x)
      return i+3;
    if (((T)1 << (i+3)) & x)
      return i+4;
    if (((T)1 << (i+4)) & x)
      return i+5;
    if (((T)1 << (i+5)) & x)
      return i+6;
    if (((T)1 << (i+6)) & x)
      return i+7;
    if (((T)1 << (i+7)) & x)
      return i+8; 
  }
	return 0;

/*	// rolled variant:
	for (uint16_t i = 0; i < sizeof(T)*8; ++i) {
		if (((T)1 << i) & x)
			return i+1;
	}
	return 0;
*/
}



template<class T>
T insert_bit(T x, uint16_t position) {
	/*
	*	Inserts the bit at specified position in x and returns it.
	*	First creates an integer with a set 1 bit at position.
	*	Then uses Disjunction to activate that bit in x.
	*/

	return x | ((T)1 << (position-1));
}



template<class T>
T delete_bit(T x, uint16_t position) {
	/*	
	*	Deletes the bit at specified position in x and returns it.
	*	First creates an integer with a set 1 bit at position. 
	*	Then that integer is inverted (so at all 1-bits except for the specified position)
	*	Conjunction is used to keep all bits of x except for that at position.
	*/

	return x & ~((T)1 << (position-1));
}


template<class T>
bool contains_bit(T x, uint16_t position) {
	/*
	*	Checks if bit at specified position is set.
	*	Creates an integer with a set 1 bit at position.
	* 	Then uses conjunction to check if remaining integer ist >0 or ==0.
	*/

	return x & ((T)1 << ((position-1)));
}


#endif // BIT_OPERATIONS_CPP
