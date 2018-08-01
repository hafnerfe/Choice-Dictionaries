/*
* 	Purpouse: Profiling of the Choice Dictionary
*	Contains two functions: to profile Choice Dictionaries,
*	and to time one Choice Dictionary
*
*	Created on 31.05.18 by Felix Hafner
*/

#ifndef PROFILER_H
#define PROFILER_H

#include "Core/Choice_dictionary/Choice_dictionary.h"
#include "Profiling_file.h"
#include "Report_file.h"
#include <vector>
#include <utility>
#include <string>


/*
*	profile_choice_dictionaries:
*	Is used to compare several Choice Dictionaries (cds) with one Profiling File.
*	Profiling_file is stored in parameter path.
*	Every CD will be timed repetition_count many times.
*	Returns a Report_file containing the results.
*/
Report_file* profile_choice_dictionaries(
		const Profiling_file& pf,
		std::vector<Choice_dictionary* >& cds,
		const std::vector<std::string> names,
		uint16_t repetition_count = 20
		);

/*
*	profile_profiling_file:
*	Is used to evaluate a (single) Choice Dictionary with multiple Profiling Files.
*	This way one can determine what a worst-case input should look like,
*	and what the bottleneck operations are.
*	Returns a Report_file containing the results.
*/
Report_file* profile_profiling_files(
		const std::vector<Profiling_file>& pfs,	
		Choice_dictionary* cd,
		const std::vector<std::string> names,
		uint16_t repetition_count = 20
		);

/*
*	time_choice_dictionary
*	Function is used by profile_profiling_files and profile_choice_dictionaries.
*	It runs a Choice Dictionary on the operations of the Profiling File and returns the time.
*/
double time_choice_dictionary(
		Choice_dictionary& cd, 
		const Profiling_file& pf
		);



#endif //PROFILER_H
