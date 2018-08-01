/*
*	Test.h Header
*	Purpose: 
*		-test the correctness of "find one" implementations.
*		-Time the different "find one" implementations.
*/

#ifndef PROFILE_FO_H
#define PROFILE_FO_H

#include "find_one_collection.h"
#include <sys/time.h>
#include <iostream>
#include <vector>
#include <numeric>
#include <string>


std::vector<uint64_t> get_random_numbers(
		uint64_t count,
		double set_bit_probability,
		uint64_t seed=1);


void profile_all(
		const std::vector<uint64_t>& numbers,
		std::string dst_path,
		std::vector<int (*) (uint64_t)> implementations=std::vector<int (*) (uint64_t)>(),
		std::vector<std::string> implementation_names=std::vector<std::string>(),
		uint8_t repetition_count=10);

std::vector<std::string> get_incorrect_implementations(
		const std::vector<uint64_t>& numbers,
		std::vector<int (*) (uint64_t)> implementations=std::vector<int (*) (uint64_t)>(),
		std::vector<std::string> implementation_names=std::vector<std::string>());


#endif
