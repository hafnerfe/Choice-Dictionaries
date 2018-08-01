/*
*	The source code for the Interface Integer_operations.h
*	Why the Header is not included: see Bit_operations.cpp
*
*	Created by Felix Hafner, 15.06.18
*/

#ifndef INTEGER_OPERATIONS_CPP
#define INTEGER_OPERATIONS_CPP


template <class T>
T get_upper(T x) {
	return x >> (sizeof(T)*4);
}


template <class T>
T get_lower(T x) {
	return (x << (sizeof(T)*4)) >> (sizeof(T)*4);
	// Alternative: return x & not(get_upper(x));
}


template <class T>
T set_upper(T x, T upper) {
	/*
	*	Replaces the upper half of x with upper and returns the Integer.
	*/

	return put_together(get_lower(x), upper);
}


template <class T>
T set_lower(T x, T lower) {
	return put_together(lower, get_upper(x));
}


template <class T>
T put_together(T lower, T upper) {
	return get_lower(lower) | (upper << (sizeof(T)*4));
}


#endif // INTEGER_OPERATIONS_CPP