/*
*	Test both Choice Dictionaries (b=32 & b=64) on several pfs.
*	Also test how slow "hiding k" is.
*/


#include "cd_dev.h"
#include <iostream>
#include <ctime>
#include "../cd_b64.h"
using namespace std;


#define PF_PATH (std::string("Profiling_files/test02_"))
#define RF_PATH (std::string("Report_files/test02_"))


#define _I (5000000)			// i
#define _J (50000000)			// j
#define _K (500000000)			// k

#define _I_S (std::to_string(_I))
#define _J_S (std::to_string(_J))
#define _K_S (std::to_string(_K))


vector<Choice_dictionary*> get_cd_vector();
vector<string> get_names_vector();

void test_impl();
void create_and_eval_pf_1();
void create_and_eval_pf_2();
void create_and_eval_pf_3();
void create_and_eval_pf_4();
void create_and_eval_pf_5();


int main() {
	test_impl();
	create_and_eval_pf_1();
	create_and_eval_pf_2();
	create_and_eval_pf_3();
	create_and_eval_pf_4();
	create_and_eval_pf_5();
	

	return 0;
}

vector<Choice_dictionary*> get_cd_vector() {
	// Tested: (b=32,normal), (b=64,normal), (b=64,k hidden).
	vector<Choice_dictionary*> cds;
	cds.push_back(create_choice_dictionary(1, cd_implementations::optimal));
	cds.push_back(new Optimal_cd_64(1));
	cds.push_back(create_choice_dictionary(1, cd_implementations::small));
	return cds;
}

vector<string> get_names_vector() {
	return {"b=32, normal", "b=64, normal", "b=64, k hidden"};
}


void test_impl() {
	Choice_dictionary* cd1 = new Optimal_cd_64(1);
	Choice_dictionary* cd2 = create_choice_dictionary(1, cd_implementations::optimal);
	Choice_dictionary* cd3 = create_choice_dictionary(1, cd_implementations::small);

	// make Prof_file.
	Profiling_file pf;
	pf.set_name("Correctness test.");
	pf.set_date();
	pf.set_max_argument_size(50000);
	auto ops = create_random_operations(500000, 50000);
	pf.add_profiling_operations(ops);
	pf.save_operations(true);
	pf.save(PF_PATH+"0.txt");

	// test both choice dictionaries:

	cout << "Checking if implementations are correct:" << endl;
	cout << "	new 64=b cd: " << test_cd(PF_PATH+"0.txt", *cd1) << endl;
	cout << "	old 32=b cd: " << test_cd(PF_PATH+"0.txt", *cd2) << endl;
	cout << "	64=b & small cd: " << test_cd(PF_PATH+"0.txt", *cd3) << endl;
}

void create_and_eval_pf_1() {
	cout<<"Creating PF_1"<<endl;
	Profiling_file pf;
	pf.set_name("test02_pf1: random operations 1.");

	pf.add_information("size: "+_I_S+". number of operations: "+_J_S);
	pf.add_information("Operations are random. Each operation has the same probability.");
	pf.set_max_argument_size(_I);
	pf.save_operations(false);

	auto ops = create_random_operations(_J, _I);
	pf.add_profiling_operations(ops);
	pf.save(PF_PATH+"1.txt");

	// Profiling
	auto cd_vector = get_cd_vector();
	auto names_vector = get_names_vector();
	cout<<"Profiling PF_1"<<endl;
	profile_cds(pf, RF_PATH+"1.txt", cd_vector, names_vector);
}

void create_and_eval_pf_2() {
	cout<<"Creating PF_2"<<endl;
	Profiling_file pf;
	pf.set_name("test02_pf2: random operations 2.");

	pf.add_information("size: "+_J_S+". number of operations: "+_J_S);
	pf.add_information("Operations are random. Each operation has the same probability.");
	pf.set_max_argument_size(_J);
	pf.save_operations(false);

	auto ops = create_random_operations(_J, _J);
	pf.add_profiling_operations(ops);
	pf.save(PF_PATH+"2.txt");

	// Profiling
	auto cd_vector = get_cd_vector();
	auto names_vector = get_names_vector();
	cout<<"Profiling PF_2"<<endl;
	profile_cds(pf, RF_PATH+"2.txt", cd_vector, names_vector);
}

void create_and_eval_pf_3() {
	cout<<"Creating PF_3"<<endl;
	Profiling_file pf;
	pf.set_name("test02_pf3: random operations 3.");

	pf.add_information("size: "+_K_S+". number of operations: "+_J_S);
	pf.add_information("Operations are random. Each operation has the same probability.");
	pf.set_max_argument_size(_K);
	pf.save_operations(false);

	auto ops = create_random_operations(_J, _K);
	pf.add_profiling_operations(ops);
	pf.save(PF_PATH+"3.txt");

	// Profiling
	auto cd_vector = get_cd_vector();
	auto names_vector = get_names_vector();
	cout<<"Profiling PF_3"<<endl;
	profile_cds(pf, RF_PATH+"3.txt", cd_vector, names_vector);
}

void create_and_eval_pf_4() {
	cout<<"Creating PF_4"<<endl;
	Profiling_file pf;
	pf.set_name("test02_pf4: random operations, no choice.");

	pf.add_information("size: "+_J_S+". number of operations: "+_J_S);
	pf.add_information("Operations are random. Each operation has the same probability. No 'choice'.");
	pf.set_max_argument_size(_J);
	pf.save_operations(false);

	auto ops = create_random_operations(
			_J, _J,
			{"insert", "contains", "delete"},
			{0.33, 0.33, 0.34});
	pf.add_profiling_operations(ops);
	pf.save(PF_PATH+"4.txt");

	// Profiling
	auto cd_vector = get_cd_vector();
	auto names_vector = get_names_vector();
	cout<<"Profiling PF_4"<<endl;
	profile_cds(pf, RF_PATH+"4.txt", cd_vector, names_vector);
}

void create_and_eval_pf_5() {
	cout<<"Creating PF_5"<<endl;
	Profiling_file pf;
	pf.set_name("test02_pf5: random operations, a lot of choice.");

	pf.add_information("size: "+_J_S+". number of operations: "+_J_S);
	pf.add_information("Operations are random. A lot of 'choice'.");
	pf.add_information("Probabilities: choice: 50%, delete: 30%, insert: 10%, contains: 10%");
	pf.set_max_argument_size(_J);
	pf.save_operations(false);

	auto ops = create_random_operations(
			_J, _J,
			{"insert", "contains", "delete", "choice"},
			{0.1, 0.1, 0.3, 0.5});
	pf.add_profiling_operations(ops);
	pf.save(PF_PATH+"5.txt");

	// Profiling
	auto cd_vector = get_cd_vector();
	auto names_vector = get_names_vector();
	cout<<"Profiling PF_5"<<endl;
	profile_cds(pf, RF_PATH+"5.txt", cd_vector, names_vector);
}



