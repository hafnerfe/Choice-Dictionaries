/*
*	Facade for the Choice Dictionary Benchmarks and Tests.
*	Provides a simplified interface to a larger body of code.
*	Aim: Make the software library easier to use, understand, and test.
*
*	wraps a collection of APIs within a single API.
*
*	This API is for developers, who want to test and profile Choice Dictionaries.
*	For users, who want to use a Choice Dictionary, see "cd.h".
*		
*	Created by Felix Hafner, 07.06.18.
*/

#ifndef CD_DEV_H
#define CD_DEV_H

#include "Core/Choice_dictionary/Choice_dictionary.h"		// Abstract Choice Dictionary.
#include "Profiling/Profiling_file.h"						// Interface for the Profiling File.
#include "Profiling/Utilities/rng.h"						// Random number generator.
#include <string>
#include <vector>
#include <utility>



/*
*	cd_modes: only serves as input argument for "create_choice_dictionary".
*		-def (default): let the program decide
*		-small: The Choice Dictionary shall take up as little space as possible.
*		-dense: The client Set of the Choice Dictionary will be big.
*		-sparse: The client Set of the Choice Dictionary will be small.
*/
enum class cd_modes {def, small, dense, sparse};
Choice_dictionary* create_choice_dictionary(uint64_t universe_size, cd_modes mode = cd_modes::def);


/*
*	cd_implementations: only serves as input for "create_choice_dictionary"
*	Refers to the specific implementations. 
*/
enum class cd_implementations{small, optimal, simple, stack};
Choice_dictionary* create_choice_dictionary(uint64_t universe_size, cd_implementations implementation);


/*
*	Profile Choice Dictionaries:
*
*	src_path specifies the path of the Profiling File.
*	dst_path specifies the path of the Report File that will be saved.
*	Every Choice Dictionary also needs a name (for the Report File).
*/
void profile_cds(
		const std::string& src_path, 
		const std::string& dst_path, 
		std::vector<Choice_dictionary*> cds, 
		const std::vector<std::string>& names);

void profile_cds(
		const Profiling_file& pf, 
		const std::string& dst_path, 
		std::vector<Choice_dictionary*> cds, 
		const std::vector<std::string>& names);


/*
*	Profile Profiling Files:
*	
*	Profiling one or more Profiling Files with only one Choice Dictionary.
*	
*/
void profile_pfs(
		const std::vector<std::string>& src_paths, 
		const std::string& dst_path, 
		Choice_dictionary* cd, 
		const std::vector<std::string>& names);

void profile_pfs(
		const std::vector<Profiling_file>& pfs, 
		const std::string& dst_path, 
		Choice_dictionary* cd, 
		const std::vector<std::string>& names);

/*
*	Testing a Choice_Dictionary:
*
*	Test the correctness of a Choice Dictionary using a Profiling File.
*/
bool test_cd(const std::string& src_path, Choice_dictionary& cd);
bool test_cd(const Profiling_file& pf, Choice_dictionary& cd);


/*
*	Creating random operations:
*
*	operations_s specifies which operations shall be used. 
*	Thus, only Subsets of {"insert", "del", "contains", "choice"} are allowed.
*	probability specifies the probability that each operation is selected.
*	If sum(probabilites) != 1, undefined behaviour.
*/
std::vector<std::pair<std::string, _t::len_t> > create_random_operations(
		uint64_t operation_count,
		_t::len_t maximum_size,
		const std::vector<std::string>& operations_s = {"insert", "del", "contains", "choice"},
		const std::vector<double>& probabilities = {0.25, 0.25, 0.25, 0.25},
		uint64_t seed=1);



#endif //CD_DEV_H
