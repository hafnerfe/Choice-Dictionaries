/*
*	Test both Choice Dictionaries (b=32 & b=64) on several pfs.
*	Also test how slow "hiding k" is.
*/

#include "cd_dev.h"
#include <iostream>
#include <ctime>
using namespace std;


#define PF_PATH (std::string("Profiling_files/test03_"))
#define RF_PATH (std::string("Report_files/test03_"))

#define _P (100)
#define _I (10000)				// i
#define _L (1000000)
#define _J (100000000)			// j
#define _K (10000000000)			// k



void create_pf_1(std::vector<Profiling_file>& pfs);
void create_pf_2(std::vector<Profiling_file>& pfs);
void create_pf_3(std::vector<Profiling_file>& pfs);
void create_pf_4(std::vector<Profiling_file>& pfs);
void create_pf_5(std::vector<Profiling_file>& pfs);
void evaluate_all(std::vector<Profiling_file>& pfs);
void create_pf_i(std::vector<Profiling_file>& pfs, uint64_t size, uint64_t ops_count, uint8_t pf_count);


int main() {
	std::vector<Profiling_file> pfs;
	//create_pf_1(pfs);
	//create_pf_2(pfs);
	//create_pf_3(pfs);
	create_pf_i(pfs,_P,_J,1);
	create_pf_i(pfs,_I,_J,2);
	create_pf_i(pfs,_L,_J,3);
	create_pf_i(pfs,_J,_J,4);
	create_pf_i(pfs,_K,_J,5);



	evaluate_all(pfs);
	return 0;
}



void create_pf_i(std::vector<Profiling_file>& pfs, uint64_t size, uint64_t ops_count, uint8_t pf_count) {
	cout << "Creating PF_"<<pf_count<<endl;
	Profiling_file pf;
	pf.set_name("test03_pf"+to_string(pf_count)+": random operations");
	pf.add_information("Just randomly selected operations");
	pf.set_max_argument_size(size);
	pf.save_operations(false);
	auto ops=create_random_operations(ops_count, size);
	pf.add_profiling_operations(ops);
	pf.save(PF_PATH+to_string(pf_count)+".txt");
	pfs.push_back(pf);
}


void evaluate_all(std::vector<Profiling_file>& pfs) {
	cout<<"Starting to profile..."<<endl;
	auto cd=create_choice_dictionary(1, cd_implementations::optimal);

	
	profile_pfs(pfs, RF_PATH+"1.txt", cd, 
		{
		"size " + to_string(_P),
		"size "+to_string(_I),
		"size "+to_string(_L),
		"size "+to_string(_J),
		"size "+to_string(_K)
		});
}



