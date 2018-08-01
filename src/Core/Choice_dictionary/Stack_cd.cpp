/*
*	Source code for the interface Stack_cd.
*
*	Created by Felix Hafner on 29.05.18
*/

#include "Stack_cd.h"
#include "Simple_cd.h"
#include <cstdlib>


#define WORD_LEN (sizeof(_t::len_t)*8)



Stack_cd::Stack_cd(_t::len_t n): 
		cd(new Simple_cd(n)){
}

Stack_cd::~Stack_cd() {
	if (cd != nullptr)
		delete cd;
	cd = nullptr;
}

_t::len_t Stack_cd::choice() {
	while(recent_inserts.size() > 0) {
		if (contains(recent_inserts.top()))
			return recent_inserts.top();
		recent_inserts.pop();
	}
	return 0;
}

bool Stack_cd::contains(_t::len_t l) {
	return cd->contains(l);
}

void Stack_cd::insert(_t::len_t l) {
	if (!cd->contains(l))
		recent_inserts.push(l);
	cd->insert(l);
}

void Stack_cd::del(_t::len_t l) {
	cd->del(l);
}

//-----------

void Stack_cd::init(_t::len_t n) {
	destroy();
	cd = new Simple_cd(n);
}
void Stack_cd::destroy() {
	if (cd != nullptr)
		delete cd;
	cd = nullptr;
}

