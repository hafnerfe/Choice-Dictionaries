/*
*	Profiler: Profiles Choice Dictionaries and creates Report file
*	Interface: users should only be interested in the method profile_choice_dictionaries
*	
*	Author: Felix Hafner
*	Created on: 31.05.18
*/

#include "Profiler.h"
#include "Operations.h"
#include <sys/time.h>
#include <numeric>
#include <ctime>
#include <iostream>
#include <cassert>



Report_file* profile_choice_dictionaries(
		const Profiling_file& pf,
		std::vector<Choice_dictionary* >& cds,
		const std::vector<std::string> names,
		uint16_t repetition_count
		) {


	assert(cds.size() == names.size());
	assert(pf.get_profiling_operations() != nullptr);
	

	// Create results vector, and warm up:
	std::vector<std::vector<double> > results (
			names.size(), std::vector<double>());
	for (uint8_t i = 0; i < names.size(); ++i) {
		cds[i]->init(pf.get_max_argument_size());
		time_choice_dictionary(*cds[i], pf);
		cds[i]->destroy();
	}
		


	// Time the Choice dictionaries and store times in results:
	for (uint16_t i = 0; i < repetition_count; ++i) {
		for (uint8_t j = 0; j < names.size(); ++j) {
			cds[j]->init(pf.get_max_argument_size());
			results[j].push_back(time_choice_dictionary(*cds[j], pf));
			cds[j]->destroy();
		}
	}

	// Create the report:
	Report_file *rf = new Report_file();
	rf->add_information("Profiling of one Profiling File and several Choice Dictionaries.");
	rf->set_profiling_file(pf);
	rf->set_repetition_count(repetition_count);
	rf->set_names(names);
	rf->set_results(results);
	rf->set_date();

	return rf;
}


Report_file* profile_profiling_files(
		const std::vector<Profiling_file>& pfs,
		Choice_dictionary* cd,
		const std::vector<std::string> names,
		uint16_t repetition_count
		) {
	assert(pfs.size() == names.size());
	for (uint16_t i = 0; i < pfs.size(); ++i)
		assert(pfs[i].get_profiling_operations()!=nullptr);
	// Create Results vector and warm up:
	std::vector<std::vector<double> > results (
			names.size(), std::vector<double>());
	for (uint16_t i = 0; i < names.size(); ++i) {
		cd->init(pfs[i].get_max_argument_size());
		time_choice_dictionary(*cd, pfs[i]);
		cd->destroy();
	}
	// Time the Profiling Files using the Choice Dictionary
	for (uint16_t i = 0; i < repetition_count; ++i) {
		for (uint16_t j = 0; j < names.size(); ++j) {
			cd->init(pfs[j].get_max_argument_size());	// Allocate entries and set all to 0.
			results[j].push_back(time_choice_dictionary(*cd, pfs[j]));
			cd->destroy();								// We don't want to keep the memory.
		}
	}

	// Create the report:
	Report_file *rf = new Report_file();
	rf->add_information("Profiling of several Profiling Files and only one Choice Dictionary.");
	rf->add_information("Paths of the Profiling Files used:");
	for (auto pf : pfs) 
		rf->add_information(pf.get_path());
	rf->set_profiling_file(pfs[0]);
	rf->set_repetition_count(repetition_count);
	rf->set_names(names);
	rf->set_results(results);
	rf->set_date();

	return rf;
}

void execute_operations(
		Choice_dictionary& cd, 
		input_ptr ops
		) {

	//volatile int a = 0;
	int a = 0;
	for (auto o : *ops) {
		switch(o.first) {

			//chose action
			case (cd_operations::insert):
				cd.insert(o.second);
				break;
			case (cd_operations::del):
				cd.del(o.second);
				break;
			case (cd_operations::contains):
				a = cd.contains(o.second);
				break;
			case (cd_operations::choice):
				a = cd.choice();
				break;
			default:		// Should not happen
				break;
		}	
	}
}


double time_choice_dictionary(
		Choice_dictionary& cd, 
		const Profiling_file& pf) {
	struct timeval  tv1, tv2;

	// Initialization Operations (not timed/profiled):
	execute_operations(cd, pf.get_init_operations());

	// Profiling Operations, timed:
	gettimeofday(&tv1, NULL);
	execute_operations(cd, pf.get_profiling_operations());
	gettimeofday(&tv2,NULL);

	// Return time
	return (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +
         		(double) (tv2.tv_sec - tv1.tv_sec);
}


