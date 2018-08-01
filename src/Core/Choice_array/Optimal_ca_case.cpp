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
Optimal_ca_case<T>::Optimal_ca_case(_ca_len_t size): 
		a(nullptr),
		k(size), 
		n(size) {

	a = (T*) malloc(sizeof(T)*size);
}

// Destructor:
template <class T>
Optimal_ca_case<T>::~Optimal_ca_case() {
	if (a)
		free(a);
	a = nullptr;
}


template <class T>
_ca_len_t Optimal_ca_case<T>::mate(_ca_len_t i) const {
	_ca_len_t j = get_upper(a[i-1]);
	if (((1 <= i && i <= k && k < j && j <= n) 
		|| (1 <= j && j <= k && k < i && i <= n)) 
		&& get_upper(a[j-1]) == i) {
		return j;
	}
	return i;
}


template <class T>
T Optimal_ca_case<T>::read(_ca_len_t i) {
	_ca_len_t j = mate(i);
	if (j <= k)	
		return 0; 			 			// i is weak exactly if mate(i) <=k
	else if (i > k) 
		return a[i-1];
	else
		return put_together(get_lower(a[i-1]),get_lower(a[j-1]));
}


template <class T>
_ca_len_t Optimal_ca_case<T>::nonzero() {
	if (k == n)
		return 0;
	return mate(n);				// Return position.
}


template <class T>
void Optimal_ca_case<T>::simple_write(_ca_len_t i, T x) {
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
void Optimal_ca_case<T>::write(_ca_len_t i, T x) {
	auto i_old=read(i);
	// does anything need to be done?
	if (x==i_old)
		return;

	// does simple_write suffice?
	if (x>0&&i_old>0) {
		simple_write(i,x);
		return;
	}

	if (x>0) {		// Insertion
		auto k_old=read(k);
		if (i<k) {		// left of border
			if (k_old==0) {				//3a
				a[k-1] = set_upper(a[k-1],(T)i);		// create matching
				a[i-1] = set_upper(a[i-1],(T)k);	// create matching
				--k;
				simple_write(i,x);
			} else {					//3c
				auto k_mate=mate(k);
				a[i-1]=set_upper(a[i-1],(T)k_mate);
				a[k_mate-1]=set_upper(a[k_mate-1],(T)i);
				a[k-1]=k_old;
				--k;
				simple_write(i,x);
			}
		} else if (i==k) {				//3b
			a[--k]=x;
		} else {		// right of border
			auto i_mate=mate(i);
			if (k_old==0) { 			//4a
				auto i_mate=mate(i);
				auto i_mate_old=read(i_mate);
				a[k-1]=set_upper(a[k-1],(T)i_mate);
				a[i_mate-1]=set_upper(a[i_mate-1],(T)k);
				--k;
				simple_write(i_mate,i_mate_old);
				a[i-1]=x;
			} else if (i_mate==k) {		//4b
				auto k_old=read(k);
				a[k-1]=k_old;
				a[i-1]=x;
				--k;
			} else {					//4c
				auto i_mate_old=read(i_mate);
				auto k_mate=mate(k);
				a[k-1]=k_old;
				a[i-1]=x;
				--k;
				a[i_mate-1]=set_upper(a[i_mate-1],(T)k_mate);
				a[k_mate-1]=set_upper(a[k_mate-1],(T)i_mate);
				simple_write(i_mate,i_mate_old);
			}
		}
	} else {		// Deletion
		if (i<=k) {	// delete left
			auto mate_i=mate(i);
			if (mate_i==k+1) { 			//5b
				++k;
			} else if (mate(k+1)==k+1) { 	//5a
				auto k_old=read(k+1);
				a[k]=set_upper(a[k],(T)mate_i);
				a[mate_i-1]=set_upper(a[mate_i-1],(T)k+1);
				++k;
				simple_write(k-1, k_old);
			} else {					//5c
				auto mate_k=mate(k+1);
				auto old_k=read(k+1);
				a[mate_i-1]=set_upper(a[mate_i-1],(T)mate_k);
				a[mate_k-1]=set_upper(a[mate_k-1],(T)mate_i);
				++k;
				simple_write(mate_k,old_k);
			}
		} else {	//delete right
			if (i==k+1) {				//6b
				++k;
			} 
			if (mate(k+1)==k+1) {		//6a
				auto old_k=read(k+1);
				++k;
				a[k-1]=set_upper(a[k-1],(T)i);
				a[i-1]=set_upper(a[i-1],(T)k);
				simple_write(k,old_k);
			} else {					//6c
				auto mate_k=mate(k+1);
				auto old_k=read(mate_k);
				a[i-1]=set_upper(a[i-1],(T)mate_k);
				a[mate_k-1]=set_upper(a[mate_k-1],(T)i);
				++k;
				simple_write(mate_k,old_k);
			}
		}

	}
}



