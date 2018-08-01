#include "find_one_collection.h"
#include <iostream>

std::vector<int (*) (uint64_t)> get_implementations(
    std::vector<std::string> &implementation_names) {

  std::vector<int (*) (uint64_t)> function_list;

  function_list.push_back(&binary_search);
  implementation_names.push_back("Binary Search");

  function_list.push_back(&naive_search);
  implementation_names.push_back("Naive search");

  function_list.push_back(&naive_search_unrolled);
  implementation_names.push_back("Naive search (loop unrolled)");

  function_list.push_back(&lib_log);
  implementation_names.push_back("Math library log2");

  function_list.push_back(&built_in);
  implementation_names.push_back("Built in ffs");

  function_list.push_back(&dummy_find_one);
  implementation_names.push_back("dummy function");

  //function_list.push_back(&fusion_trees);
  //implementation_names.push_back("fusion trees");

  return function_list;
}

std::vector<int (*) (uint64_t)> get_implementations() {
  std::vector<std::string> vec;
  return get_implementations(vec);
}

int binary_search(const uint64_t number) {
	uint64_t i = 0, j = 63, pos = 64;	
  if (!number)
    return 0;
	while (i <= j && pos == 64) {
		uint64_t k = (i+j)/2;
		if (((uint64_t)1 << k) & number) {
			return k+1;
    } else if (((uint64_t)1 << k) < number)
			i = k+1;
		else
			j=k-1;
	}
	return pos+1;
}


int naive_search(const uint64_t number) {
	for (uint64_t index = 0; index < 64; ++index) {
		if ((1<<index)&number)
			return index + 1;
	}	
	return 0;
}

int naive_search_unrolled(const uint64_t number) {
  for (uint64_t i = 0; i < 64;i+=8) {
    if ((1 << (i)) & number)
      return i+1;
    if ((1 << (i+1)) & number)
      return i+2;
    if ((1 << (i+2)) & number)
      return i+3;
    if ((1 << (i+3)) & number)
      return i+4;
    if ((1 << (i+4)) & number)
      return i+5;
    if ((1 << (i+5)) & number)
      return i+6;
    if ((1 << (i+6)) & number)
      return i+7;
    if ((1 << (i+7)) & number)
      return i+8; 
  }
  return 0;
}


int lib_log(const uint64_t number) {
	return log2(number)+1;
}


// GCC!
int built_in(const uint64_t number) {
  return __builtin_ffsll(number);
}



int dummy_find_one(const uint64_t number) {
  return number;
}

#include <iostream>
using namespace std;

int fusion_trees(const uint64_t number) {

  cout << "input: " << number << endl;
  uint64_t top_bits=number&0x8080808080808080;
  uint64_t all_but_top_bits=number&0x7F7F7F7F7F7F7F7F;
  uint64_t pc = ~(0x8080808080808080-all_but_top_bits)&0x8080808080808080;
  uint64_t ne=top_bits&pc;
  uint64_t summary= ((ne * 0x2040810204081)>>56)>>1;
  uint64_t cmpp2 = ~(0xFFBF9F8F87838180-(0x0101010101010101 * summary))&0x8080808080808080;
  uint64_t idxMsbyte= ((cmpp2 >> 7) * 0x0808080808080808) >> 56;
  uint64_t msbyte=((number>>idxMsbyte)&0xFF)>>1;
  uint64_t cmpp2_=~(0xFFBF9F8F87838180-(0x0101010101010101 * msbyte))&0x8080808080808080;
  uint64_t idxMsbit= ((cmpp2_ >> 7) * 0x0101010101010101) >> 56;
  cout << "output: " << (idxMsbyte | idxMsbit) << endl;
  return idxMsbyte | idxMsbit;
}



