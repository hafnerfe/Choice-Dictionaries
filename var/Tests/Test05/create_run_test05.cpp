/*
*
*/

#include "cd_dev.h"
#include <iostream>
#include <ctime>
using namespace std;


#define PF_PATH (std::string("Profiling_files/test05_"))
#define RF_PATH (std::string("Report_files/test05_"))


#define _I (2000000000)				// i, i%64=0



void create_pf_1(std::vector<Profiling_file>& pfs);
void create_pf_2(std::vector<Profiling_file>& pfs);
void evaluate_all(std::vector<Profiling_file>& pfs);


int main() {
	std::vector<Profiling_file> pfs;
	create_pf_1(pfs);
	create_pf_2(pfs);

	evaluate_all(pfs);
	return 0;
}

void create_pf_1(std::vector<Profiling_file>& pfs) {
	cout << "Creating PF_1"<<endl;
	Profiling_file pf;
	pf.set_name("test05_pf1: inserting, choice, deleting, choice");
	pf.add_information("for (l=n-64;i>64;l-=64) {");
	pf.add_information("	insert(l); choice() }");
	pf.add_information("and then delete and choice back up");
	pf.set_max_argument_size(_I);
	pf.save_operations(false);
	for (uint64_t l = _I-64; l > 0; l -=64) {
		pf.add_profiling_operation("insert",l);
		pf.add_profiling_operation("choice",0);
	}
	for (uint64_t l = 64; l<_I; l += 64) {
		pf.add_profiling_operation("delete",l);
		pf.add_profiling_operation("choice",0);
	}
	pf.save(PF_PATH+"1.txt");
	pfs.push_back(pf);
}
void create_pf_2(std::vector<Profiling_file>& pfs) {
	cout << "Creating PF_2"<<endl;
	Profiling_file pf;
	pf.set_name("test05_pf1: inserting, choice, deleting, choice");
	pf.add_information("for (l=n;i>64;l-=64) {");
	pf.add_information("	insert(l); choice() }");
	pf.add_information("and then delete and choice back up");
	pf.set_max_argument_size(_I);
	pf.save_operations(false);
	for (uint64_t l = _I; l > 0; l -=64) {
		pf.add_profiling_operation("insert",l);
		pf.add_profiling_operation("choice",0);
	}
	for (uint64_t l = 64; l<_I; l += 64) {
		pf.add_profiling_operation("delete",l);
		pf.add_profiling_operation("choice",0);
	}
	pf.save(PF_PATH+"2.txt");
	pfs.push_back(pf);
}
void evaluate_all(std::vector<Profiling_file>& pfs) {
	cout<<"Starting to profile..."<<endl;
	auto cd=create_choice_dictionary(1, cd_implementations::optimal);

	
	profile_pfs(pfs, RF_PATH+"1.txt", cd, 
		{"slow", "fast"});
}



