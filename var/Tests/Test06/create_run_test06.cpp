/*
*
*/

#include "cd_dev.h"
#include <iostream>
#include <ctime>
using namespace std;


#define PF_PATH (std::string("Profiling_files/test06_"))
#define RF_PATH (std::string("Report_files/test06_"))


//#define _I (1000000)				// v1 size
//#define _I (10000000)				//v2 size
#define _I 10000000
#define _J (100000000)			//count



void create_empty_pf_i(
	std::vector<Profiling_file>& pfs, 
	std::vector<double> probs,
	uint8_t pf_count);
void create_full_pf_i(
		std::vector<Profiling_file>& pfs, 
		std::vector<double> probs,
		uint8_t pf_count);
void evaluate_all(std::vector<Profiling_file>& pfs);


int main() {
	std::vector<Profiling_file> pfs;
	create_full_pf_i(pfs,{0.7,0.1,0.1,0.1},1);
	create_empty_pf_i(pfs,{0.7,0.1,0.1,0.1},2);
	create_full_pf_i(pfs,{0.1,0.7,0.1,0.1},3);
	create_empty_pf_i(pfs,{0.1,0.7,0.1,0.1},4);
	create_full_pf_i(pfs,{0.1,0.1,0.7,0.1},5);
	create_empty_pf_i(pfs,{0.1,0.1,0.7,0.1},6);
	create_full_pf_i(pfs,{0.1,0.1,0.1,0.7},7);
	create_empty_pf_i(pfs,{0.1,0.1,0.1,0.7},8);

	evaluate_all(pfs);
	return 0;
}

void create_empty_pf_i(
		std::vector<Profiling_file>& pfs, 
		std::vector<double> probs,
		uint8_t pf_count) {
	cout << "Creating PF_"<<(int) pf_count<<endl;
	Profiling_file pf;
	pf.set_name("test05_pf"+to_string(pf_count)+": random_tests (full)");
	pf.add_information("(empty) probs: insert, delete, contains, choice");
	for (auto p:probs)
		pf.add_information(to_string(p));
	pf.set_max_argument_size(_I);
	pf.save_operations(false);
	auto ops= create_random_operations(_J,_I,
		{"insert","delete","contains","choice"}, probs);
	pf.add_profiling_operations(ops);
	pf.save(PF_PATH+to_string(pf_count)+".txt");
	pfs.push_back(pf);
}

void create_full_pf_i(
		std::vector<Profiling_file>& pfs, 
		std::vector<double> probs,
		uint8_t pf_count) {
	cout << "Creating PF_"<<(int) pf_count<<endl;
	Profiling_file pf;
	pf.set_name("test05_pf"+to_string(pf_count)+": random_tests (empty)");
	pf.add_information("(full) probs: insert, delete, contains, choice");
	for (auto p:probs)
		pf.add_information(to_string(p));
	pf.set_max_argument_size(_I);
	pf.save_operations(false);
	for (uint64_t i = _I; i >= 1; --i) {
		pf.add_init_operation("insert",i);
	}
	auto ops= create_random_operations(_J,_I,
		{"insert","delete","contains","choice"}, probs);
	pf.add_profiling_operations(ops);
	pf.save(PF_PATH+to_string(pf_count)+".txt");
	pfs.push_back(pf);
}

void evaluate_all(std::vector<Profiling_file>& pfs) {
	
	auto cd=create_choice_dictionary(1, cd_implementations::optimal);

	cout<<"Starting to profile..."<<endl;
	profile_pfs(pfs, RF_PATH+"1.txt", cd, 
		{"1","2","3","4","5","6","7","8"});
}



