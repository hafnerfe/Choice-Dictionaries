/*
*	A small Choice Dictionary.
*	Choice Dictionary from "An optimal Choice Dictionary" by T. Hagerup
*	Not using any subclasses and hiding k in the first entry.
*	Also, the boolean value "is_full" is hidden in the universe_size 
*	and thus, the most significant bit should not be accessed.
*	This class is intended to just be small, not be readable.
*
*	Created by Felix Hafner, 23.06.18
*/

#ifndef SMALL_CD_H
#define SMALL_CD_H

#include "Choice_dictionary.h"
#include "types.h"

namespace small_cd{
	typedef __uint128_t entry_t;
}

class Small_cd : public Choice_dictionary {
		

		// Constants and Variables:
		_t::len_t universe_size;							// upper bit should not be used!
		small_cd::entry_t *a;								// where entries are stored					
		// bool is_full;									// removed: takes up 8 bytes!
		
	
		bool is_full() const;
		void set_full(bool full);
		_t::len_t get_N() const;
		_t::len_t get_k() const;
		void increase_k();
		void decrease_k();

		_t::len_t mate(_t::len_t i) const;
		void simple_write(_t::len_t i, small_cd::entry_t x);

		small_cd::entry_t read(_t::len_t i) const;
		_t::len_t nonzero() const;
		void write(_t::len_t i, small_cd::entry_t x);
		
	public:
		// Constructor and Deconstructor:
		Small_cd(_t::len_t n);
		~Small_cd();

		// Choice Dictionary operations:
		void insert(_t::len_t l) override;
		void del(_t::len_t l) override;
		bool contains(_t::len_t l) override;
		_t::len_t choice() override;

		

		void init(_t::len_t n) override;
		
		void destroy() override;
};

#endif	// SMALL_CD_H