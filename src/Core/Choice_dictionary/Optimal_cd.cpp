/*
*	The source code for the interface defined in Optimal_cd.h.
*	All operations are implemented as expected.
*
*	Created by Felix Hafner, 29.05.18
*/

#include "Optimal_cd.h"						// Interface
#include "Core/Utilities/Bit_operations.h"	// insert_bit, delete_bit, contains_bit, find_one
#include "Core/Choice_array/Optimal_ca.h"	// the choice array

#define TWO_B (sizeof(_t::entry_t)*8)


//--------------------------------------------------------------------
// Helper Functions:

inline _t::len_t choice_array_position(_t::len_t i) {
	/*
	*	converts a number in the terms of a choice_array.
	*	It returns the position of the entry corresponding i in the choice_array.
	*/

	return (((i-1)/TWO_B)+1);
}


inline _t::len_t entry_position(_t::len_t i) {
	/*
	*	converts a number in the terms of a word.
	*	It returns the position of the bit corresponding i in a 2b-bit word.
	*/

	return (((i-1)%TWO_B)+1);
}



//--------------------------------------------------------------------
// Definition of declared Choice Dictionary functions:

Optimal_cd::Optimal_cd(_t::len_t n) {
	/*
	*	Constructor for the Optimal Choice Dictionary.
	*	Takes the universe size n as parameter. Only reason to save n is for exceptions.
	*	Initializes the Choice Array with the optimal Choice Array (all operations in constant time).
	*/

	choice_array = new Optimal_ca<_t::entry_t>(n/TWO_B+((n%TWO_B)?1:0));
}

Optimal_cd::~Optimal_cd() {
	/*
	*	Deconstructor for the Optimal Choice Dictionary.
	*/
	
	if (choice_array != nullptr)
		delete choice_array;
	choice_array=nullptr;
}


void Optimal_cd::insert(_t::len_t l) {
	/*
	*	Manipulates the corresponding bit in choice_array.
	*/

	auto array_entry = choice_array->read(choice_array_position(l));
	array_entry = insert_bit(array_entry, entry_position(l));
	choice_array->write(choice_array_position(l),array_entry);
}


void Optimal_cd::del(_t::len_t l) {
	/*
	*	Manipulates the corresponding bit in choice_array.
	*/
	
	auto array_entry = choice_array->read(choice_array_position(l));
	array_entry = delete_bit(array_entry, entry_position(l));
	choice_array->write(choice_array_position(l),array_entry);
}


bool Optimal_cd::contains(_t::len_t l) {
	/*
	*	Checks the corresponding bit in choice_array.
	*/
	
	auto array_entry = choice_array->read(choice_array_position(l));
	return contains_bit(array_entry, entry_position(l));
}


_t::len_t Optimal_cd::choice() {
	/*
	*	Searches for a set bit in a nonzero-entry of the choice_array.
	*/
	
	auto position = choice_array->nonzero();
	if (position == 0) 
		return 0;
	auto array_entry = choice_array->read(position);

	return TWO_B*(position-1)+find_one(array_entry);
	
}

//--------------------------------------------------------------------
// Temporary functions that may be deleted later, depending on how profiling will work

void Optimal_cd::init(_t::len_t n) {
	choice_array = new Optimal_ca<_t::entry_t>(n/TWO_B+((n%TWO_B)?1:0));
}

void Optimal_cd::destroy() {
	if (choice_array == nullptr)
		delete choice_array;
	choice_array = nullptr;
}

