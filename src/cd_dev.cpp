/*
*	Implementation for the interface for developers.
*
*	Created by Felix Hafner, 07.06.18
*/

#include "cd_dev.h"
#include "Core/Choice_dictionary/Optimal_cd.h"
#include "Core/Choice_dictionary/Simple_cd.h"
#include "Core/Choice_dictionary/Small_cd.h"
#include "Core/Choice_dictionary/Stack_cd.h"
#include "Profiling/Profiler.h"
#include "Profiling/Report_file.h"
#include "Tests/Test_cd.h"
#include "Profiling/Operations.h"
#include <ctime>
#include <sstream>
#include <cassert>
#include <numeric>


Choice_dictionary* create_choice_dictionary(uint64_t universe_size, cd_implementations implementation) {
	switch(implementation) {
		case (cd_implementations::small):
			return new Small_cd(universe_size);
		case (cd_implementations::optimal):
			return new Optimal_cd(universe_size);
		case (cd_implementations::simple):
			return new Simple_cd(universe_size);
		case (cd_implementations::stack):
			return new Stack_cd(universe_size);
		default:
			break;
	}
}


Choice_dictionary* create_choice_dictionary(uint64_t universe_size, cd_modes mode) {

	Choice_dictionary *cd;
		switch(mode) {
			case (cd_modes::def):
				if (universe_size < 100000)
					cd = new Simple_cd(universe_size);
				else
					cd = new Optimal_cd(universe_size);
				break;
			case (cd_modes::small):
				if (universe_size < 100000)
					cd = new Simple_cd(universe_size);
				else
					cd = new Small_cd(universe_size);
				break;
			case (cd_modes::dense):
				cd = new Simple_cd(universe_size);
				break;
			case (cd_modes::sparse):
				if (universe_size < 10000)
					cd = new Stack_cd(universe_size);
				else
					cd = new Optimal_cd(universe_size);
				break;
			default:
				break;
		}
	return cd;
}


void profile_cds(
		const std::string& src_path, 
		const std::string& dst_path, 
		std::vector<Choice_dictionary*> cds, 
		const std::vector<std::string>& names
		) {
	
	assert(cds.size() == names.size());
	Profiling_file pf(src_path);
	Report_file *rf = profile_choice_dictionaries(pf, cds, names);
	rf->save(dst_path);
	delete rf;
}

void profile_cds(
		const Profiling_file& pf, 
		const std::string& dst_path, 
		std::vector<Choice_dictionary*> cds, 
		const std::vector<std::string>& names
		) {
	
	assert(cds.size() == names.size());
	Report_file *rf = profile_choice_dictionaries(pf, cds, names);
	rf->save(dst_path);
	delete rf;
}


void profile_pfs(
		const std::vector<std::string>& src_paths, 
		const std::string& dst_path, 
		Choice_dictionary* cd, 
		const std::vector<std::string>& names
		) {

	assert(src_paths.size() == names.size());
	std::vector<Profiling_file> pfs;
	for (auto s:src_paths)
		pfs.push_back(Profiling_file(s));
	Report_file *rf = profile_profiling_files(pfs, cd, names);
	rf->save(dst_path);
	delete rf;
}

void profile_pfs(
		const std::vector<Profiling_file>& pfs, 
		const std::string& dst_path, 
		Choice_dictionary* cd, 
		const std::vector<std::string>& names
		) {

	assert(pfs.size() == names.size());
	Report_file *rf = profile_profiling_files(pfs, cd, names);
	rf->save(dst_path);
	delete rf;
}


bool test_cd(const std::string& src_path, Choice_dictionary& cd) {
	Profiling_file pf(src_path);
	return test_choice_dictionary(pf, cd);
}

bool test_cd(const Profiling_file& pf, Choice_dictionary& cd) {
	return test_choice_dictionary(pf, cd);
}



std::vector<std::pair<std::string, _t::len_t> > create_random_operations(
		uint64_t operation_count,
		_t::len_t maximum_size,
		const std::vector<std::string>& operations_s,
		const std::vector<double>& probabilities,
		uint64_t seed
		) {

	assert(operations_s.size() == probabilities.size());
	assert(std::accumulate(probabilities.begin(), probabilities.end(), 0.0) >= 0.99);
	assert(std::accumulate(probabilities.begin(), probabilities.end(), 0.0) <= 1.01);

	std::vector<std::pair<std::string, uint64_t> > operation_pair_vector;

	srng(seed);		// call seed.
	for (uint64_t i = 0; i < operation_count; ++i) {
		_t::len_t arg = get_random_number(maximum_size-1)+1;		// 1 <= arg <= maximum_size
		uint8_t o = get_random_number((uint8_t)100);				// 0 <= o <= 99
		uint8_t current_threshold = 0;
		for (uint8_t j = 0; j < operations_s.size(); ++j) {
			current_threshold += probabilities[j]*100;
			if (o <= current_threshold) {
				operation_pair_vector.push_back(std::make_pair(operations_s[j], arg));
				break;
			}
		}
	}
	return operation_pair_vector;
}

