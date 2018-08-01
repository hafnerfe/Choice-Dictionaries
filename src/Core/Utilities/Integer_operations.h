/*
*	Integer_operations.h: Interface that defines some useful operations on integers.
*	To use these functions, only #include this file at the start of your code.
*	You do not need to compile the source code (i.e. Integer_operations.cpp).
*
*	Created by Felix Hafner, 15.06.18
*/

#ifndef INTEGER_OPERATIONS_H
#define INTEGER_OPERATIONS_H


// get_upper will return the upper (most significant) half of x.
template <class T>
T get_upper(T x);


// get_lower will return the lower (least significant) half of x.
template <class T>
T get_lower(T x);


// insert_upper will take upper and replace get_upper(x) with upper. The modified integer is returned.
template <class T>
T set_upper(T x, T upper);


// insert_lower will take lower and replace get_lower(x) with lower. The modified integer is returned.
template <class T>
T set_lower(T x, T lower);


// put_together takes two halves (upper, lower), puts them together and returns that integer.
template <class T>
T put_together(T lower, T upper);



// See Bit_operations.h for why we need to include the source code.

#include "Integer_operations.tpp"

#endif 	// INTEGER_OPERATIONS_H
