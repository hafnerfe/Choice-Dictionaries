#include "profile_fo.h"
#include <fstream>
#include <iostream>
#include <cassert>
#include <ctime>
#include "rng.h"


double profile_one(
		int(*find_one) (uint64_t) , 
		const std::vector<uint64_t>& numbers
		) {
	struct timeval tv1,tv2;
	int res=0;
	gettimeofday(&tv1,NULL);

	for (auto n:numbers) {
		res=find_one(n);
	}

	gettimeofday(&tv2,NULL);
	return (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +
         		(double) (tv2.tv_sec - tv1.tv_sec);
}




void save_results(
		const std::vector<std::vector<double> >& results,
		const std::string& dst_path,
		const std::vector<std::string>& names
		) {

	std::ofstream file;
	file.open(dst_path);
	assert(file.is_open());

	time_t now=time(0);
	std::string date=ctime(&now);
	while(!date.empty() && date[date.length()-1]=='\n')
		date.erase(date.length()-1);
	file << date << "\n\n\n";

	for (uint8_t i = 0; i < results.size(); ++i) {
		auto current_result = results[i];
		double sum = std::accumulate(current_result.begin(), current_result.end(), 0.0);
		double mean = sum / current_result.size();

		double sq_sum = std::inner_product(
			current_result.begin(), current_result.end(), current_result.begin(), 0.0);
		double stdev = std::sqrt(sq_sum / current_result.size() - mean * mean);

		file << names[i] << std::endl;
		file << "mean: " << mean << std::endl;
		file << "stdev: " << stdev << std::endl;
		file << "max: " << *max_element(
			current_result.begin(), current_result.end())
			 << std::endl;
		file << "min: " << *min_element(
			current_result.begin(), current_result.end())
			<< "\n\n";
	}

	file.close();
}

std::vector<uint64_t> get_random_numbers(
		uint64_t count,
		double set_bit_probability,
		uint64_t seed
		) {
	std::vector<uint64_t> numbers;
	srng(seed);
	for (uint64_t i = 0; i < count; ++i) {
		numbers.push_back(get_random_number<uint64_t>(set_bit_probability));	
	}
	return numbers;
}


void profile_all(
		const std::vector<uint64_t>& numbers,
		std::string dst_path,
		std::vector<int (*) (uint64_t)> implementations,
		std::vector<std::string> implementation_names,
		uint8_t repetition_count
		) {

	std::vector<std::vector<double> > results;
	assert(implementations.size() == implementation_names.size());
	if (implementations.size() == 0) 
		implementations = get_implementations(implementation_names);
	for (size_t i = 0; i < implementations.size(); ++i) {
		results.push_back(std::vector<double>());
	}

	// time implementations:
	for (uint16_t c = 0; c < repetition_count; ++c) {
		for (size_t i = 0; i < implementations.size(); ++i) {
			results[i].push_back(profile_one(implementations[i], numbers));
		}
	}
	save_results(results, dst_path, implementation_names);
}


std::vector<std::string> get_incorrect_implementations(
		const std::vector<uint64_t>& numbers,
		std::vector<int (*) (uint64_t)> implementations,
		std::vector<std::string> implementation_names
		) {

	assert(implementations.size() == implementation_names.size());
	if (implementations.size() == 0) 
		implementations = get_implementations(implementation_names);
	std::vector<std::string> incorrect;
	for (size_t i = 0; i < implementations.size(); ++i) {
		for (auto n:numbers) {
			uint16_t result=implementations[i](n);
			if (!result) {		//	Check if result is 0
				if (n) {
					incorrect.push_back(implementation_names[i]);
					break;
				} else {
					continue;
				}
			}
			if (!(n&((uint64_t)1 << (result-1)))) {
				incorrect.push_back(implementation_names[i]);
				break;
			}
		}
	}
	return incorrect;
}

