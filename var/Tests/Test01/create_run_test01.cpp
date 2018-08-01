#include "cd_dev.h"
#include <iostream>
#include <ctime>
using namespace std;

#define SIZE 1000000
#define SIZE_s (std::to_string(SIZE))
#define PF_PATH (std::string("Profiling_files/test01_"))
#define RF_PATH (std::string("Report_files/test01.txt"))


void create_pf_1() {
	/*
	*	PF_1:
	*	Testing the Operation "choice"
	*	Repeatedly call Choice on empty CD.
	*/
	cout << "Test01: Creating PF_1..." << endl;
	Profiling_file pf;
	pf.set_date();
	pf.set_name("test01_1: Testing choice.");
	pf.set_max_argument_size(SIZE);
	pf.add_information("Testing the Operation 'choice'");
	pf.add_information("The CD will be empty, with n="+
		SIZE_s+std::string(", and choice will be called repeatedly"));
	pf.add_information("choice will be called n times");	
	for (uint32_t i = 1; i <= SIZE; ++i) {
		pf.add_profiling_operation("choice", 0);
	}
	pf.save(PF_PATH + "1.txt");
}



void create_pf_2() {
	/*
	*	PF_2:
	*	Testing the Operation "choice".
	*	Repeatedly call Choice on empty CD just containing n.
	*/
	cout << "Test01: Creating PF_2..." << endl;
	Profiling_file pf;
	pf.set_date();
	pf.set_name("test01_2: Testing Choice");
	pf.set_max_argument_size(SIZE);
	pf.add_information("Testing the Operation 'choice'");
	pf.add_information("The CD will only contain n, with n="+
		SIZE_s+std::string(", and choice will be called repeatedly"));
	pf.add_information("choice will be called n times");
	pf.add_init_operation("insert", SIZE);
	for (uint32_t i = 1; i <= SIZE; ++i) {
		pf.add_profiling_operation("choice", 0);
	}
	pf.save(PF_PATH + "2.txt");
}


void create_pf_3() {
	/*
	*	PF_3:
	*	Testing the Operation "choice".
	*	Repeatedly call Choice on empty CD just containing 1.
	*/
	cout << "Test01: Creating PF_3..." << endl;
	Profiling_file pf;
	pf.set_date();
	pf.set_name("test01_3: Testing Choice");
	pf.set_max_argument_size(SIZE);
	pf.add_information("Testing the Operation 'choice'");
	pf.add_information("The CD will only contain 1, with n="+SIZE_s+
		std::string(", and choice will be called repeatedly"));
	pf.add_information("choice will be called n times");
	pf.add_init_operation("insert", 63);
	for (uint32_t i = 1; i <= SIZE; ++i) {
		pf.add_profiling_operation("choice", 0);
	}
	pf.save(PF_PATH + "3.txt");
}

void create_pf_4() {
	/*
	*	PF_4:
	*	Testing the Operation "contains".
	*	Call contains for 1...n on empty CD
	*/
	cout << "Test01: Creating PF_4..." << endl;
	Profiling_file pf;
	pf.set_date();
	pf.set_name("test01_4: Testing Contains");
	pf.set_max_argument_size(SIZE);
	pf.add_information("Testing the Operation 'contains'");
	pf.add_information("The CD will be completely empty, with n="+SIZE_s);
	pf.add_information("Contains will be called on 1...n");
	for (uint32_t i = 1; i <= SIZE; ++i) {
		pf.add_profiling_operation("contains", i);
	}
	pf.save(PF_PATH+"4.txt");
}

void create_pf_5() {
	/*
	*	PF_5:
	*	Testing the Operation "contains".
	*	Call contains for 1...n on full CD
	*/
	cout << "Test01: Creating PF_5..." << endl;
	Profiling_file pf;
	pf.set_date();
	pf.set_name("test01_5: Testing Contains");
	pf.set_max_argument_size(SIZE);
	pf.add_information("Testing the Operation 'contains'");
	pf.add_information("The CD will be completely full, with n="+SIZE_s);
	pf.add_information("Contains will be called on 1...n");
	for (uint32_t i = 1; i <= SIZE; ++i) {
		pf.add_init_operation("insert", i);
	}
	for (uint32_t i = 1; i <= SIZE; ++i) {
		pf.add_profiling_operation("contains", i);
	}
	pf.save(PF_PATH+"5.txt");
}

void create_pf_6() {
	/*
	*	PF_6:
	*	Testing the Operation "insert"
	*	Call insert for 1...n on empty CD
	*/
	cout << "Test01: Creating PF_6..." << endl;
	Profiling_file pf;
	pf.set_date();
	pf.set_name("test01_6: Testing insert");
	pf.set_max_argument_size(SIZE);
	pf.add_information("Testing the Operation insert.");
	pf.add_information("The CD will be completely empty, with n="+SIZE_s);
	pf.add_information("Insert will be called on 1...n.");
	for (uint32_t i = 1; i <= SIZE; ++i) {
		pf.add_profiling_operation("insert", i);
	}
	pf.save(PF_PATH+"6.txt");
}

void create_pf_7() {
	/*
	*	PF_7:
	*	Testing the Operation "insert"
	*	Call insert for n...1 on empty CD
	*/
	cout << "Test01: Creating PF_7..." << endl;
	Profiling_file pf;
	pf.set_date();
	pf.set_name("test01_7: Testing insert");
	pf.set_max_argument_size(SIZE);
	pf.add_information("Testing the Operation insert.");
	pf.add_information("The CD will be completely empty, with n="+SIZE_s);
	pf.add_information("Insert will be called on n...1.");
	for (uint32_t i = SIZE; i >= 1; --i) {
		pf.add_profiling_operation("insert", i);
	}
	pf.save(PF_PATH+"7.txt");
}

void create_pf_8() {
	/*
	*	PF_8:
	*	Testing the Operation "insert"
	*	Call insert for n-128,...1 on empty CD.
	*/
	cout << "Test01: Creating PF_8..." << endl;
	Profiling_file pf;
	pf.set_date();
	pf.set_name("test01_8: Testing insert");
	pf.set_max_argument_size(SIZE);
	pf.add_information("Testing the Operation insert.");
	pf.add_information("The CD will be completely empty with n="+SIZE_s);
	pf.add_information("Insert will be called on n-128....1");
	for (uint32_t i = SIZE-128; i >=1; --i) {
		pf.add_profiling_operation("insert", i);
	}
	pf.save(PF_PATH+"8.txt");

}

void create_pf_9() {
	/*
	*	PF_9:
	*	Testing the Operation "insert"
	*	Call isnert for 1...n on full CD
	*/
	cout << "Test01: Creating PF_9..." << endl;
	Profiling_file pf;
	pf.set_date();
	pf.set_name("test01_9: Testing insert");
	pf.set_max_argument_size(SIZE);
	pf.add_information("Testing the Operation insert.");
	pf.add_information("The CD will be completely full, with n="+SIZE_s);
	pf.add_information("Insert will be called on 1...n.");
	for (uint32_t i = 1; i <= SIZE; ++i) {
		pf.add_init_operation("insert", i);
	}
	for (uint32_t i = 1; i <= SIZE; ++i) {
		pf.add_profiling_operation("insert", i);
	}
	pf.save(PF_PATH+"9.txt");
}


void create_pf_10() {
	/*
	*	PF_10:
	*	Testing the Operation "delete"
	*	Call delete for 1...n on full CD
	*/
	cout << "Test01: Creating PF_10..." << endl;
	Profiling_file pf;
	pf.set_date();
	pf.set_name("test01_10: Testing delete.");
	pf.add_information("Testing the Operation delete.");
	pf.add_information("The CD will be completely full, with n="+SIZE_s);
	pf.add_information("Delete will be called on 1...n.");
	for (uint32_t i = 1; i <= SIZE; ++i) {
		pf.add_init_operation("insert", i);
	}
	for (uint32_t i = 1; i <= SIZE; ++i) {
		pf.add_profiling_operation("delete", i);
	}
	pf.save(PF_PATH+"10.txt");
}

void create_pf_11() {
	/*
	*	PF_11:
	*	Testing the Operation "delete"
	*	Call delete for 128...n on full CD
	*/
	cout << "Test01: Creating PF_11..." << endl;
	Profiling_file pf;
	pf.set_date();
	pf.set_name("test01_11: Testing delete.");
	pf.add_information("Testing the Operation delete.");
	pf.add_information("The CD will be completely full, with n="+SIZE_s);
	pf.add_information("Delete will called on 2...n");
	for (uint32_t i = SIZE; i >= 1; --i) {	// Fill from top
		pf.add_init_operation("insert", i);
	} 
	for (uint32_t i = 128; i <= SIZE; ++i) {
		pf.add_profiling_operation("delete", i);
	}
	pf.save(PF_PATH+"11.txt");
}

void create_pf_12() {
	/*
	*	PF_12:
	*	Testing the Operation "delete".
	*	Call delete for n...1 on full CD.
	*/
	cout << "Test01: Creating PF_12..." << endl;
	Profiling_file pf;
	pf.set_date();
	pf.set_name("test01_12: Testing delete.");
	pf.add_information("Testing the operation delete.");
	pf.add_information("The CD will be completely full, with n="+SIZE_s);
	pf.add_information("Delete will be called on n...1");
	for (uint32_t i = 1; i <= SIZE; ++i) {
		pf.add_init_operation("insert", i);
	} 
	for (uint32_t i = SIZE; i >= 1; --i) {
		pf.add_profiling_operation("delete", i);
	}
	pf.save(PF_PATH+"12.txt");
}

void evaluate_all() {
	std::vector<std::string> paths;
	std::vector<std::string> names;
	for (int i = 1; i <= 12; ++i) {
		names.push_back(std::to_string(i));
		paths.push_back(PF_PATH+std::to_string(i)+std::string(".txt"));
	}
	Choice_dictionary* cd = create_choice_dictionary(SIZE, cd_implementations::optimal);

	
	cout << "starting to profile..." << endl;
	profile_pfs(paths, RF_PATH, cd, names);
	cout << "done profiling." << endl;

	return;

	cout << "Test case 2:" << test_cd(paths[1], *cd) << endl;

	cout << "Test case 3:" << test_cd(paths[2], *cd) << endl;
	
}

int main() {
	srand(time(NULL));
	create_pf_1();
	create_pf_2();
	create_pf_3();
	create_pf_4();
	create_pf_5();
	create_pf_6();
	create_pf_7();
	create_pf_8();
	create_pf_9();
	create_pf_10();
	create_pf_11();
	create_pf_12();

	evaluate_all();

	cout << "all done!" << endl;
	return 0;
}


