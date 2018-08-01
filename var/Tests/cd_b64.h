/*
*	Just defining the usual optimal cd with b=64.
*/


#include "cd_dev.h"
#include "types.h"
#include "Core/Choice_array/Choice_array.h"
#include "Core/Utilities/Bit_operations.h"
#include "Core/Choice_array/Optimal_ca.h"
using namespace std;


typedef __uint128_t new_entry_t;	// 2b=128, b=64

uint16_t my_find_one(__uint128_t x) {
	uint64_t lower_half = (uint64_t) x;
	if (lower_half)
		return __builtin_ffsll(lower_half);
	uint64_t upper_half = (uint64_t) (x>>64);
	if (upper_half)
		return 64+__builtin_ffsll(upper_half);
	return 0;
}


// Choice dict (optimal from the paper) with b=64. (b=w)
class Optimal_cd_64 : public Choice_dictionary{
		Choice_array<new_entry_t>* choice_array;	

		inline _t::len_t choice_array_position(_t::len_t i) {
			return (((i-1)/128)+1);
		}
		inline _t::len_t entry_position(_t::len_t i) {

			return (((i-1)%128)+1);
		}
	public:

		// Constructor and Destructor:
		Optimal_cd_64(_t::len_t n) {
			choice_array = new Optimal_ca<new_entry_t>(n/128+((n%128)?1:0));
		}
		~Optimal_cd_64() {
			if (choice_array != nullptr)
				delete choice_array;
			choice_array=nullptr;
		}
		void insert(_t::len_t l) override {
			auto array_entry = choice_array->read(choice_array_position(l));
			array_entry = insert_bit(array_entry, entry_position(l));
			choice_array->write(choice_array_position(l),array_entry);
		}
		void del(_t::len_t l) override {
			auto array_entry = choice_array->read(choice_array_position(l));
			array_entry = delete_bit(array_entry, entry_position(l));
			choice_array->write(choice_array_position(l),array_entry);
		}
		bool contains(_t::len_t l) override {
			auto array_entry = choice_array->read(choice_array_position(l));
			return contains_bit(array_entry, entry_position(l));
		}
		_t::len_t choice() override {
			_t::len_t position = choice_array->nonzero();
			if (position == 0) 
				return 0;
			auto array_entry = choice_array->read(position);
			return 128*(position-1)+my_find_one(array_entry);
		}
		void init(_t::len_t n) override {
				choice_array = new Optimal_ca<new_entry_t>(n/128+((n%128)?1:0));
		}
		void destroy() override {
			if (choice_array == nullptr)
				delete choice_array;
			choice_array = nullptr;
		}
};
