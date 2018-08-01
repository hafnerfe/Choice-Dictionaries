/*
*
*/


#include "cd_dev.h"
#include "types.h"
#include "Core/Choice_array/Choice_array.h"
#include "Core/Utilities/Bit_operations.h"
#include "Core/Choice_array/Optimal_ca.h"
#include "Core/Choice_dictionary/Simple_cd.h"
#include <iostream>
using namespace std;


// Choice dict (optimal from the paper) with b=64. (b=w)
class Perm_cd : public Choice_dictionary{
		_t::len_t *permutation, *inverse_permutation;
		_t::len_t k;
	public:

		// Constructor and Destructor:
		Perm_cd(_t::len_t n) : 
			permutation(nullptr),
			inverse_permutation(nullptr),
			k(0) {
			permutation=(_t::len_t*) malloc(sizeof(_t::len_t)*(n));
			inverse_permutation=(_t::len_t*) malloc(sizeof(_t::len_t)*(n));
		}
		~Perm_cd() {
			if (inverse_permutation != nullptr)
				free(inverse_permutation);
			if (permutation != nullptr)
				free(inverse_permutation);
		}
		void insert(_t::len_t l) override {
			if (!contains(l)) {
				permutation[k]=l-1;
				inverse_permutation[l-1]=k;
				++k;
			}
		}
		void del(_t::len_t l) override {
			if (contains(l)) {
				permutation[inverse_permutation[l-1]]=permutation[--k];
				inverse_permutation[permutation[k]]=inverse_permutation[l-1];
			}
		}
		bool contains(_t::len_t l) override {
			auto new_i=inverse_permutation[l-1];
			if (new_i<k && permutation[new_i]==l-1)
				return true;
			return false;
		}
		_t::len_t choice() override {
			if (k==0)
				return 0;
			return permutation[0]+1;
		}
		void init(_t::len_t n) override {
			k=0;
			permutation=(_t::len_t*) malloc(sizeof(_t::len_t)*n);
			inverse_permutation= (_t::len_t*) malloc(sizeof(_t::len_t)*n);
		}
		void destroy() override {
			if (inverse_permutation!=nullptr)
				free(inverse_permutation);
			if (permutation!=nullptr)
				free(permutation);
		}
};


