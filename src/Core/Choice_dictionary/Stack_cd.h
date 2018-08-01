/*
*	Interface for Stack_cd. It uses a stack to keep track of recent inserts.
*	Probably quick, but big space requirements.
*
*	Created by Felix Hafner on 29.05.18
*/

#ifndef STACK_CD_H
#define STACK_CD_H

#include "Choice_dictionary.h"
#include "types.h"
#include <stack>



class Stack_cd : public Choice_dictionary {
		Choice_dictionary* cd;
		std::stack<_t::len_t> recent_inserts;	// This might take up O(nlogn) bits.
						// Depending on implementation, sometimes even more
	public:

		Stack_cd(_t::len_t n);
		~Stack_cd();
		
		_t::len_t choice() override;
		bool contains(_t::len_t l) override;
		void insert(_t::len_t l) override;
		void del(_t::len_t l) override;

		void init(_t::len_t n) override;
		void destroy() override;
};

#endif //STACK_CD_H
