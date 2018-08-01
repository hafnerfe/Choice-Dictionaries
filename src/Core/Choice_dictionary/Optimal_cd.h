/*
*	The interface for the Optimal_cd. It extends the interface Choice_dictionary.
*	It uses an optimal choice array, which makes this choice dictionary optimal.
*	Other than that all operations are as expected.
*	_t::len_t and _t::entry_t are defined in types.h (included in Choice_dictionary.h).
*
*	Created by Felix Hafner, 29.05.18
*/

#ifndef OPTIMAL_CD_H
#define OPTIMAL_CD_H


#include "Choice_dictionary.h"				// Defines the Interface for this class
#include "types.h"				// _t::len_t and _t::entry_t
#include "Core/Choice_array/Choice_array.h"	// Defines the Interface to a Choice Array



class Optimal_cd : public Choice_dictionary {

		Choice_array<_t::entry_t>* choice_array;	

	public:

		// Constructor and Destructor:
		Optimal_cd(_t::len_t n);
		~Optimal_cd();
		
		// Operations of a Choice Dictionary:
		void insert(_t::len_t l) override;
		void del(_t::len_t l) override;
		bool contains(_t::len_t l) override;
		_t::len_t choice() override;

		// Operations needed for Profiling:
		void init(_t::len_t n) override;
		void destroy() override;
};

#endif //OPTIMAL_CD_H
