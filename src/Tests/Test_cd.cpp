/*
*	This is the implementation for Test_cd.h
*
*	Created by Felix Hafner, 05.06.18
*/

#include "Test_cd.h"
#include "Profiling/Operations.h"
#include <cstdlib>
#include <string>
#include <cstdint>

//#define _DEBUG
#ifdef _DEBUG
#include <iostream>
using namespace std;
#endif


void print_debug(std::string operation, uint64_t argument) {
#ifdef _DEBUG
	cout << operation << ": " << argument << endl;
#endif
}


bool check_choice(Choice_dictionary& cd, bool *a, uint64_t len) {
	uint64_t tmp = cd.choice();
#ifdef _DEBUG
	cout << "choice result: " << tmp << endl;
#endif
	if (tmp && !a[tmp-1])
		return false;
	else if (tmp == 0) {
		for (uint64_t i = 0; i < len; ++i) {
			if (a[i])
				return false;
		}
	}
	return true;
}


bool check_all_entries(Choice_dictionary &cd, bool *a, uint64_t len) {
	for (uint64_t i = 1; i <= len; ++i) {
		if (a[i-1] != cd.contains(i))
			return false;	
	}
	
	return true;
}


bool test_choice_dictionary(const Profiling_file& pf, Choice_dictionary& cd) {

	/*
	* 	a is to keep track of operations and to ensure cd is correct.
	*	Run through profiling file, execute the operations, and check what happens.
	*	Ignores default_operations
	*/

	
	bool *a = (bool *) calloc(pf.get_max_argument_size(), sizeof(bool));
	cd.init(pf.get_max_argument_size());

	// Check if all entries ar empty / 0:
	for (uint64_t i = 1; i <= pf.get_max_argument_size(); ++i) {
		if (cd.contains(i))
			return false;
	}

	// Execute Operations:
	for (auto o : *(pf.get_profiling_operations())) {
		switch(o.first) {
			//chose action

			case (cd_operations::insert):
				print_debug("Inserting", o.second);
				cd.insert(o.second);
				a[o.second-1] = true;
				break;

			case (cd_operations::del):
				print_debug("Deleting", o.second);
				cd.del(o.second);
				a[o.second-1] = false;
				break;

			case (cd_operations::contains):
				print_debug("Contains", o.second);
				if (cd.contains(o.second) != a[o.second-1])
					return false;
				break;

			case (cd_operations::choice):
				print_debug("Choice",0);
				if (!check_choice(cd, a, pf.get_max_argument_size()))
					return false;

			default:			// Should not happen
				break;
		}
	}	
	
	// Run over every entry and check:
	return check_all_entries(cd,a,pf.get_max_argument_size());
}


std::vector<bool> test_choice_dictionaries(const std::string path, std::vector<Choice_dictionary>& cds) {
	std::vector<bool> results;
	for (uint16_t i = 0; i < cds.size(); ++i) {
		results.push_back(test_choice_dictionary(path, cds[i]));
	}
	return results;
}

