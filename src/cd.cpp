/*
*	Implementation of the API cd.h
*	For more information on the pimpl Idiom see:
*		https://en.cppreference.com/w/cpp/language/pimpl
*		https://en.wikipedia.org/wiki/Opaque_pointer
*	
*	The cd_impl is also a factory object, choosing which Choice dictionary
*	fits best.
*	
*	Created by Felix Hafner, 04.07.18
*/

#include "Core/Choice_dictionary/Choice_dictionary.h"
#include "Core/Choice_dictionary/Optimal_cd.h"
#include "Core/Choice_dictionary/Simple_cd.h"
#include "Core/Choice_dictionary/Small_cd.h"
#include "Core/Choice_dictionary/Stack_cd.h"
#include "cd.h"
#include <cassert> 

struct cd::cd_impl {
	/*
	*	Will take care of choosing the appropriate Choice Dictionary (in the Constructor).
	*	Will also check if inputs are in a certain bound.
	*/
	private:
		std::unique_ptr<Choice_dictionary> cd;
		_t::len_t universe_size;

		void check_index(_t::len_t i) {
			// Checks if index is in range. 0<i<=n.
			assert(i > 0);
			assert(i <= universe_size);
		}

	public:
	
		cd_impl(_t::len_t n) : universe_size(n) {
			// Choose strategy (this is a factory)
			
			if (n < 100000)
				cd = std::make_unique<Simple_cd>(n);
			else if (n < 100000000)
				cd = std::make_unique<Stack_cd>(n);
			else 
				cd = std::make_unique<Optimal_cd>(n);
		}


		void insert(_t::len_t i) {
			check_index(i);
			cd->insert(i);
		}
		void del(_t::len_t i) {
			check_index(i);
			cd->del(i);
		}
		_t::len_t choice() {
			return cd->choice();
		}
		bool contains(_t::len_t i) {
			check_index(i);
			return cd->contains(i);
		}
};


// Constructors:
cd::cd(_t::len_t n) : 
		cd_pimpl(std::make_unique<cd_impl>(n)) {
}

cd::cd(_t::len_t n, std::vector<_t::len_t> init_list) : 
		cd_pimpl(std::make_unique<cd_impl>(n)) {

	for (auto i : init_list)
		insert(i);
}

/*	important for pimpl to work.
* 	for more information:
* 	https://stackoverflow.com/questions/9954518/stdunique-ptr-with-an-incomplete-type-wont-compile
*/
cd::~cd() {}	// Default Deconstructor.	

void cd::insert(_t::len_t i) {
	cd_pimpl->insert(i);
}

void cd::del(_t::len_t i) {
	cd_pimpl->del(i);
}

_t::len_t cd::choice() {
	return cd_pimpl->choice();
}

bool cd::contains(_t::len_t i) {
	return cd_pimpl->contains(i);
}


