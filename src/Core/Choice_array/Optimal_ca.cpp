/*
*	This is the source code for the Interface Optimal_ca.h
*
*	Created by Felix Hafner, 18.06.18
*/

#include "Core/Utilities/Integer_operations.h"
#include <cstdint>
#include <cstdlib>


// Constructor:
template <class T>
Optimal_ca<T>::Optimal_ca(_ca_len_t size): 
		a(nullptr),
		k(size), 
		n(size) {

	a = (T*) malloc(sizeof(T)*size);
	if (a==nullptr)
		exit(EXIT_FAILURE);
}

// Destructor:
template <class T>
Optimal_ca<T>::~Optimal_ca() {
	if (a)
		free(a);
	a = nullptr;
}


template <class T>
_ca_len_t Optimal_ca<T>::mate(_ca_len_t i) const {
	_ca_len_t j = get_upper(a[i-1]);
	if (((1 <= i && i <= k && k < j && j <= n) 				\
			|| (1 <= j && j <= k && k < i && i <= n)) 		\
			&& get_upper(a[j-1]) == i) {
		return j;
	}
	return i;
}


template <class T>
T Optimal_ca<T>::read(_ca_len_t i) {
	_ca_len_t j = mate(i);
	if (j <= k)	
		return 0; 			 			// i is weak exactly if mate(i) <=k
	else if (i > k) 
		return a[i-1];
	else
		return put_together(get_lower(a[i-1]),get_lower(a[j-1]));
}


template <class T>
_ca_len_t Optimal_ca<T>::nonzero() {
	if (k == n)
		return 0;
	return mate(n);				// Return position.
}


template <class T>
void Optimal_ca<T>::simple_write(_ca_len_t i, T x) {
	if (i <= k) {				// Matching exists.
		a[i-1] = set_lower(a[i-1], get_lower(x));
		a[mate(i)-1]= set_lower(a[mate(i)-1], get_upper(x));
	} else {
		a[i-1] = x;
		_ca_len_t j = mate(i);
		if (j != i) 
			a[j-1] = set_upper(a[j-1], (T) j); 	// Eliminate a spurious matching edge.
	}
}


template <class T>
void Optimal_ca<T>::write(_ca_len_t i, T x) {

	T x_0  = read(i);
	_ca_len_t j = mate(i);
	if (x != 0) {
		if (x_0 == 0) {					// an insertion.
			_ca_len_t k_pr = mate(k);
			T u_0 = read(k);
			k--;
			simple_write(k+1,u_0); 		// Reestablish value of a[k].
			if (i != k_pr) {
				a[j-1] = set_upper(a[j-1], (T) k_pr);

				a[k_pr-1] = set_upper(a[k_pr-1], (T) j);
				a[k_pr-1] = set_lower(a[k_pr-1], get_lower(a[i-1]));
			}
		}
		simple_write(i,x);
	} else {
		if (x_0 != 0) {					// a deletion.
			_ca_len_t k_pr = mate(k+1);	
			T v = read(k_pr);
			k++;
			a[j-1] = set_upper(a[j-1], (T) k_pr);
			a[k_pr-1] = set_upper(a[k_pr-1], (T) j);
			if (k_pr != i)
				simple_write(k_pr, v);
		}
	}
}




