/*
*	Bit_operations.h: Interface that defines some useful bit operations.
*	To use these functions, only #include this file at the start of your code.
*	You do not need to compile the source code (i.e. Bit_operations.cpp).
*
*	Created by Felix Hafner, 15.06.18.
*/

#ifndef BIT_OPERATIONS_H
#define BIT_OPERATIONS_H


#include <cstdint>


// 	find_one will return the position of an arbitrary set bit in x.
//	If there is none (i.e. x == 0), then 0 is returned.
//	Implementation in .tpp
template<class T>
uint16_t find_one(T x);


//	Implementation in .cpp
#ifdef __GNUC__
template<>
uint16_t find_one<uint64_t>(uint64_t x);

template<>
uint16_t find_one<__uint128_t>(__uint128_t x);
#endif


//	insert_bit will insert a set (1) bit into x at the specified position.
//	Valid positions are 1,...,sizeof(T)*8.
//	The resulting x is returned.
template<class T>
T insert_bit(T x, uint16_t position);


//	delete bit will set a bit to 0 in x at the specified position.
//	Valid positions are 1,...,sizeof(T)*8.
//	The resulting x is returned.
template<class T>
T delete_bit(T x, uint16_t position);


// Contains bit will check if bit at position is set or not.
// Valid positions are 1,...,sizeof(T)*8.
template<class T>
bool contains_bit(T x, uint16_t position);



/*
*	C++ doesn't allow us to cleanly seperate Interface from Implementations with templates.
*	Thus, we have to include the source file at the end.
*	Because of that, you only need to include this file in your project, and not compile it.
*	It will also copy the source code into your project. 
*	Consequence: Longer compile time.
*/
#include "Bit_operations.tpp"

#endif 		// BIT_OPERATIONS_H
