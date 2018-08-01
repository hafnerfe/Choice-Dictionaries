/*
*	Defining the API for the Choice Dictionary.
*	This is for users of the Choice Dictionary, not creators/profilers.
*
*	Created by Felix Hafner, 04.07.18
*/

#ifndef CD_H
#define CD_H

#include "types.h"						// defines _t::len_t
#include <memory>						// smart pointers
#include <vector>						// initialization list (constructor)
#include <experimental/propagate_const>	// for Pimpl


/*
*	Class cd:
*	
*	This class is a facade/interface, defining the API.
*	It uses the pimpl (Pointer to implementation) idiom, to hide
*	the implementation and reduce compile time (also to reduce dependencies).
*	
*	For this to work, the deconstructor has to be declared inside the function body,
*	but the definition has to be where cd_impl is defined.
*/


class cd {
	private:
		// Pimpl idiom:
		struct cd_impl;	
		std::experimental::propagate_const<std::unique_ptr<cd_impl> > cd_pimpl;

	public:

		cd(_t::len_t n);
		// every element in init_list will be inserted into the Choice Dictionary:
		cd(_t::len_t n, std::vector<_t::len_t> init_list);
		~cd();

		void insert(_t::len_t i);
		void del(_t::len_t i);
		_t::len_t choice();
		bool contains(_t::len_t i);

};

#endif // CD_H
