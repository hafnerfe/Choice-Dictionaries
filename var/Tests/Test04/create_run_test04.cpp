/*
*	Test both Choice Dictionaries (b=32 & b=64) on several pfs.
*/

#include "cd_dev.h"
#include <iostream>
#include <ctime>
using namespace std;


#define PF_PATH (std::string("Profiling_files/test04_"))
#define RF_PATH (std::string("Report_files/test04_"))


#define _I (100000000)				// i
//#define _I (100000)				// i



void create_pf_1(std::vector<Profiling_file>& pfs);
void create_pf_2(std::vector<Profiling_file>& pfs);
void create_pf_3(std::vector<Profiling_file>& pfs);
void create_pf_4(std::vector<Profiling_file>& pfs);
void create_pf_5(std::vector<Profiling_file>& pfs);
void create_pf_6(std::vector<Profiling_file>& pfs);
void evaluate_all(std::vector<Profiling_file>& pfs);


int main() {
	std::vector<Profiling_file> pfs;
	create_pf_1(pfs);
	create_pf_2(pfs);
	create_pf_3(pfs);
	create_pf_4(pfs);
	create_pf_5(pfs);
	create_pf_6(pfs);


	evaluate_all(pfs);
	return 0;
}

void create_pf_1(std::vector<Profiling_file>& pfs) {
	cout << "Creating PF_1"<<endl;
	Profiling_file pf;
	pf.set_name("test04_pf1: insert n...1, empty");
	pf.set_max_argument_size(_I);
	pf.save_operations(false);
	for (uint64_t i = _I; i > 0; --i) {
		pf.add_profiling_operation("insert",i);
	}
	pf.save(PF_PATH+"1.txt");
	pfs.push_back(pf);
}
void create_pf_2(std::vector<Profiling_file>& pfs) {
	cout << "Creating PF_2"<<endl;
	Profiling_file pf;
	pf.set_name("test04_pf2: insert 1...n, empty");
	pf.set_max_argument_size(_I);
	pf.save_operations(false);
	for (uint64_t i = 1; i <=_I; ++i) {
		pf.add_profiling_operation("insert",i);
	}
	pf.save(PF_PATH+"2.txt");
	pfs.push_back(pf);
}
void create_pf_3(std::vector<Profiling_file>& pfs) {
	cout << "Creating PF_3"<<endl;
	Profiling_file pf;
	pf.set_name("test04_pf3: insert (n-64),...1, empty");
	pf.set_max_argument_size(_I);
	pf.save_operations(false);
	for (uint64_t i = _I-65; i > 0; --i) {
		pf.add_profiling_operation("insert",i);
	}
	pf.save(PF_PATH+"3.txt");
	pfs.push_back(pf);
}
void create_pf_4(std::vector<Profiling_file>& pfs) {
	cout << "Creating PF_4"<<endl;
	Profiling_file pf;
	pf.set_name("test04_pf4: delete 1,...,n, full");
	pf.set_max_argument_size(_I);
	pf.save_operations(false);
	for (uint64_t i = _I; i > 0; --i) {
		pf.add_init_operation("insert",i);
	}
	for (uint64_t i = 1; i <=_I; ++i) {
		pf.add_profiling_operation("delete",i);
	}
	pf.save(PF_PATH+"4.txt");
	pfs.push_back(pf);
}
void create_pf_5(std::vector<Profiling_file>& pfs) {
	cout << "Creating PF_5"<<endl;
	Profiling_file pf;
	pf.set_name("test04_pf5: delete n,...,1 full");
	pf.set_max_argument_size(_I);
	pf.save_operations(false);
	for (uint64_t i = _I; i > 0; --i) {
		pf.add_init_operation("insert",i);
	}
	for (uint64_t i = _I; i >=1; --i) {
		pf.add_profiling_operation("delete",i);
	}
	pf.save(PF_PATH+"5.txt");
	pfs.push_back(pf);
}
void create_pf_6(std::vector<Profiling_file>& pfs) {
	cout << "Creating PF_6"<<endl;
	Profiling_file pf;
	pf.set_name("test04_pf6: delete 65,...,n full");
	pf.set_max_argument_size(_I);
	pf.save_operations(false);
	for (uint64_t i = _I; i > 0; --i) {
		pf.add_init_operation("insert",i);
	}
	for (uint64_t i=65; i <= _I ; ++i) {
		pf.add_profiling_operation("delete",i);
	}
	pf.save(PF_PATH+"5.txt");
	pfs.push_back(pf);
}
void evaluate_all(std::vector<Profiling_file>& pfs) {
	cout<<"Starting to profile..."<<endl;
	auto cd=create_choice_dictionary(1, cd_implementations::optimal);

	
	profile_pfs(pfs, RF_PATH+"1.txt", cd, 
		{"ins 1,...,n",
		"ins n,...1",
		"ins (n-64),...,1",
		"del 1,...,n",
		"del n,...,1",
		"del 65,...,n"});
}



