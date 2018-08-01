/*
*
*
*	Created by Felix Hafner, 23.06.18
*/

#include <cstdlib>
#include "Small_cd.h"
#include "Core/Utilities/Integer_operations.h"
#include "Core/Utilities/Bit_operations.h"

#define B (sizeof(small_cd::entry_t)*8/2)
#define TWO_B (sizeof(small_cd::entry_t)*8)
#define N (universe_size/TWO_B+((universe_size%TWO_B ? 1:0)))


small_cd::entry_t set_upper_lower(small_cd::entry_t x, small_cd::entry_t i) {
	return get_lower(x) | ((x>>(B+B/2)) << (B+B/2)) | ((i << (B+B/2))>>(B/2));
}
small_cd::entry_t get_upper_lower(small_cd::entry_t x) {
	return (x << (B/2))>>(B/2+B);
}

//-----------------------------------------------
// Private member helper functions:

bool Small_cd::is_full() const {
	// Checks if the CA is full.
	return universe_size >> (sizeof(_t::len_t)*8-1);
}

void Small_cd::set_full(bool full) {
	if (full)	// Add the most significant bit.
		universe_size |= ((_t::len_t)1 << (sizeof(_t::len_t)*8-1));
	else		// Remove the most significant bit.
		universe_size &= ~((_t::len_t)1 << (sizeof(_t::len_t)*8-1));
}

_t::len_t Small_cd::get_N() const {
	auto real_universe_size = (universe_size << 1) >> 1; // just shift away most significant bit.
	return (real_universe_size/TWO_B) + (real_universe_size%TWO_B ? 1:0);
}

_t::len_t Small_cd::get_k() const {
	if (is_full())
		return 0;
	else
		return a[0] >> (B+B/2);
}

void Small_cd::decrease_k() {
	if (!is_full()) {
		a[0] = (get_lower(a[0])) | ((get_upper(a[0]) << (B+B/2))>>B/2) | (((small_cd::entry_t)get_k()-1) << (B+B/2));
		if (get_k() <= 0)	// Set is_full to true.
			set_full(true);
	}
}

void Small_cd::increase_k() {
	small_cd::entry_t k = get_k();
	a[0] = ((a[0] << (B/2)) >> (B/2)) | ((k+1) << (B+B/2));
	// Set is_full to false.
	set_full(false);
}

//-----------------------------------------------
// Private Choice Array functions: 

_t::len_t Small_cd::mate(_t::len_t i) const{
	small_cd::entry_t j = get_upper_lower(a[i-1]);
	if (((1 <= i && i <= get_k() && get_k() < j && j <= get_N()) 
		|| (1 <= j && j <= get_k() && get_k() < i && i <= get_N())) 
		&& get_upper_lower(a[j-1]) == i) {
		return j;
	}
	return i;
}


small_cd::entry_t Small_cd::read(_t::len_t i) const {
	if (mate(i) <= get_k())
		return 0; 			 		//i is weak exactly if mate(i) <=k
	else if (i > get_k()) 
		return a[i-1];
	else
		return put_together(get_lower(a[i-1]),get_lower(a[mate(i)-1]));
}


_t::len_t Small_cd::nonzero() const {
	if (get_k() == get_N()) 
		return 0;
	return mate(get_N());
}


void Small_cd::simple_write(_t::len_t i, small_cd::entry_t x) {
	if (i <= get_k()) {
		a[i-1] = set_lower(a[i-1], get_lower(x));
		a[mate(i)-1] = set_lower(a[mate(i)-1], get_upper(x));
	} else {
		a[i-1] = x;
		small_cd::entry_t j = mate(i);
		if (j != i) {
			a[j-1] = set_upper_lower(a[j-1], j); //Eliminate a spurious matching edge
		}
	}
}


void Small_cd::write(_t::len_t i, small_cd::entry_t x) {
	small_cd::entry_t x_0  = read(i);
	auto j = mate(i);
	if (x != 0) {
		if (x_0 == 0) {				//an insertion
			auto k_pr = mate(get_k());
			small_cd::entry_t u = read(get_k());	
			decrease_k();
			simple_write(get_k()+1,u); 	//Reestablish value of a[k]
			if (i != k_pr) {
				a[j-1]=set_upper_lower(a[j-1],(small_cd::entry_t)k_pr);
				a[k_pr-1]=set_upper_lower(a[k_pr-1],(small_cd::entry_t)j);
				a[k_pr-1]=set_lower(a[k_pr-1], get_lower(a[i-1]));
			}
		}
		simple_write(i,x);
	} else {
		if (x_0 != 0) {				//a deletion
			_t::len_t k_pr = mate(get_k()+1);	
			small_cd::entry_t v = read(k_pr);
			increase_k();
			a[j-1]=set_upper_lower(a[j-1],(small_cd::entry_t)k_pr);
			a[k_pr-1]=set_upper_lower(a[k_pr-1],(small_cd::entry_t)j);
			if (k_pr != i)
				simple_write(k_pr, v);
		}
	}
}

//-----------------------------------------------
// Public Functions: 

Small_cd::Small_cd(_t::len_t n): universe_size(n) {
	a = (small_cd::entry_t*) malloc(sizeof(small_cd::entry_t)*get_N());
	if (a==nullptr)
		exit(EXIT_FAILURE);
	a[0]=((small_cd::entry_t) get_N() << (B+B/2)); //set k to N
}

Small_cd::~Small_cd() {
	if (a)
		free(a);
	a = nullptr;
}

void Small_cd::init(_t::len_t n) {
	universe_size=n;
	destroy();
	a = (small_cd::entry_t*) malloc(sizeof(small_cd::entry_t)*N);
	if (a==nullptr)
		exit(EXIT_FAILURE);
	a[0]=((small_cd::entry_t) get_N() << (B+B/2)); //set k to N
}

void Small_cd::destroy() {
	if (a) {
		free(a);
		a=nullptr;
	}
}

void Small_cd::insert(_t::len_t l) {
	_t::len_t i = ((l-1)/(TWO_B))+1;
	auto array_entry = read(i);
	array_entry= insert_bit(array_entry, ((l-1) % (TWO_B))+1);
	write(i,array_entry);
}

void Small_cd::del(_t::len_t l) {
	_t::len_t i = ((l-1)/(TWO_B))+1;
	auto array_entry = read(i);
	array_entry = delete_bit(array_entry, ((l-1) % (TWO_B))+1);
	write(i,array_entry);
}

bool Small_cd::contains(_t::len_t l) {
	_t::len_t i = ((l-1)/(TWO_B))+1;
	auto array_entry = read(i);
	return (array_entry & ((small_cd::entry_t)1 << ((l-1)%(TWO_B))));
}

_t::len_t Small_cd::choice() {
	auto i = nonzero();
	if (i == 0)
		return 0;
	auto array_entry = read(i);
	return TWO_B*(i-1)+find_one(array_entry);
	
}

