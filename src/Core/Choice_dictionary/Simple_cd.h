/*
*	The interface for a simple Choice Dictionary.
*
*	Created by Felix Hafner, 29.05.18
*/

#ifndef SIMPLE_CD_H
#define SIMPLE_CD_H

#include "Choice_dictionary.h"
#include "types.h"
#include <cstdlib>

#define WORD_LEN (sizeof(_t::len_t)*8)

class Simple_cd : public Choice_dictionary {
	 
		_t::len_t universe_size;			// only needed if exceptions are wanted.
		_t::len_t *s;
		_t::len_t size_s;

	public:

		Simple_cd(_t::len_t n);
		~Simple_cd();
		void insert(_t::len_t l) override;
		bool contains(_t::len_t l) override;
		void del(_t::len_t l) override;
		_t::len_t choice() override;

		void init(_t::len_t n) override;
		void destroy() override;
};

#endif //SIMPLE_CD_H
