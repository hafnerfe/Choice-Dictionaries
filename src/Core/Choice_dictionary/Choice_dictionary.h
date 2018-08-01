/*
* 	This is the Interface defining the operations for a Choice Dictionary.
*
*	Created by Felix Hafner, 29.05.18
*/

#ifndef CHOICE_DICTIONARY_H
#define CHOICE_DICTIONARY_H

#include "types.h"


class Choice_dictionary {
	public:
		virtual ~Choice_dictionary() = default;

		virtual void insert(_t::len_t l) = 0;
		virtual void del(_t::len_t l) = 0;
		virtual bool contains(_t::len_t l) = 0;
		virtual _t::len_t choice() = 0;

		virtual void init(_t::len_t n) = 0;
		virtual void destroy() = 0;
};


#endif //CHOICE_DICTIONARY_H
