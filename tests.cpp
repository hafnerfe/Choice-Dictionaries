/*
* 	This is the main module, to test the library and the ui-facade
*/

#include "src/cd_dev.h"
#include "src/cd.h"
#include <iostream>
#include <ctime>


using namespace std;

void uno();
void dos();
void tres();
void cuatro();
void cinco();
void seis();		// Check CA concern

int main() {
	//seis();
	//exit(2);
	cinco();
	exit(1);
	dos();
	tres();
	cuatro();
	return 0;
}

#include "src/Core/Choice_array/Optimal_ca.h"

void seis() {
	auto a = new Optimal_ca<uint64_t>(3);
	a->write(1,1);
	a->write(2,1);
	a->write(1,0);
	uint64_t e = 5;
	e = set_upper(e, (uint64_t) 1);
	a->write(3,e);
	cout << "0 is correct: " << (uint64_t) a->read(1) << endl;
	cout << "now with choice dict. " << endl;
	Choice_dictionary* c = create_choice_dictionary(64*3, cd_implementations::optimal);
	c->insert(5);
	c->insert(68);
	c->del(5);
	c->insert(64*2+15);
	c->insert(64*2+32); // create incorrect matching
	//for (uint8_t i = 1; i < 64; ++i)
		cout << "0 is correct: " << (int) c->contains(5) << endl;
}

void cinco() {
	//testing the write with cases.
	Choice_dictionary* c=create_choice_dictionary(1,cd_implementations::optimal);
	Profiling_file pf;
	pf.add_profiling_operations(create_random_operations(100000,1000));
	pf.set_max_argument_size(1000);
	cout << "testing...:" << (int)test_cd(pf,*c) << endl;
}

void cuatro() {
	Choice_dictionary*  c= create_choice_dictionary(1000000, cd_implementations::optimal);
	c->insert(1000000);
	cout << "start test 2. (inserted 1000000)" << endl;
	for (uint32_t i = 0; i < 10000000; ++i) {
		//c->choice();
	}
	cout << "done." << endl;
	Choice_dictionary* c2 = create_choice_dictionary(1000000, cd_implementations::optimal);
	c2->insert(1); 
	cout << "start test 3. (inserted 1)" << endl;
	for (uint32_t i = 0; i < 10000000; ++i) {
		c2->choice();
	}
	cout << "done." << endl;
}

void dos() {
	cd c(100);
	cout << "0:" << c.contains(28) << endl;
	c.insert(49);
	c.insert(69);
	cout << "49/69: " << c.choice() << endl;
	cout << "0: " << c.contains(68) << endl;
	cout << "1: " << c.contains(49) << endl;
	c.del(49);
	cout << "0: " << c.contains(49) << endl;

	cd c2(40, {4,40});
	cout << "40/4:" << c2.choice() << endl;
	cout << "1: " << c2.contains(40) << endl;

	cout << "expecting assertion failed:" << endl;
	c2.insert(41);
}

void tres() {
	std::string path("var/Profiling_files/");

	Profiling_file pf;
	cout << "creating random operations..." << endl;
	auto o = create_random_operations(5000,10000000000000);
	cout << "done creating random operations: " << o.size() << endl;
	pf.add_profiling_operations(o);
	cout << "done adding the operations to the pf." << endl;
	pf.set_name("Million Random Operations.");
	pf.set_date();
	pf.add_information("Just random ops, created with library function.");
	pf.set_max_argument_size(10000000000000);
	pf.save(path+"1_6-1_6_random.txt");
	cout << "done creating the Profiling file." << endl;

	vector<Choice_dictionary*> cds;
	cds.push_back(create_choice_dictionary(1, cd_implementations::small));
	cds.push_back(create_choice_dictionary(10, cd_implementations::optimal));
	cds.push_back(create_choice_dictionary(10, cd_implementations::simple));
	cds.push_back(create_choice_dictionary(10, cd_implementations::stack));

	cout << "Done creating the Choice Dictionaries" << endl;
/*
	cout << "small: " << test_cd(path+"1_6-1_6_random.txt", *cds[0]) << endl;
	cout << "optimal: " << test_cd(path+"1_6-1_6_random.txt", *cds[1]) << endl;
	cout << "simple: " << test_cd(path+"1_6-1_6_random.txt", *cds[2]) << endl;
	cout << "stack: " << test_cd(path+"1_6-1_6_random.txt", *cds[3]) << endl;

	cout << "Done testing" << endl;
*/
	profile_cds(path+"1_6-1_6_random.txt", "var/Report_files/1_6-1_6_random.txt", cds,
		 {"small","optimal","simple","stack"});

	for (auto cd : cds)
 		delete cd;

}


void uno() {
	std::string path("var/Profiling_files/");

	Profiling_file pf;
	auto o = create_random_operations(1000, 1000);
	pf.add_profiling_operations(o);
	o = create_random_operations(20,1000, {"insert", "delete"}, {0.8, 0.2});
	pf.add_init_operations(o);
	pf.set_date();
	pf.set_name("Random operations");
	pf.add_information("Init Operations just insert and delete");
	pf.set_max_argument_size(1000);
	pf.save(path+"1_3-1_3_random.txt");
	
	pf = Profiling_file();
	o = create_random_operations(1000, 5000);
	pf.add_profiling_operations(o);
	o = create_random_operations(20,5000, {"insert", "delete"}, {0.8, 0.2});
	pf.add_init_operations(o);
	pf.set_date();
	pf.set_name("Random operations");
	pf.add_information("Init Operations just insert and delete");
	pf.set_max_argument_size(5000);
	pf.save(path+"5_3-1_3_random.txt");

	vector<Choice_dictionary*> cds;
	cds.push_back(create_choice_dictionary(0, cd_implementations::small));
	cds.push_back(create_choice_dictionary(1000, cd_implementations::optimal));
	cds.push_back(create_choice_dictionary(5000, cd_implementations::simple));
	cds.push_back(create_choice_dictionary(1000, cd_implementations::stack));
	vector<std::string> names{ "small", "optimal", "simple", "stack"};
	//cout << "small: " << test_cd(path+"1_3-1_3_random.txt", *cds[0]) << endl;
	cout << "optimal: " << test_cd(path+"1_3-1_3_random.txt", *cds[1]) << endl;
	cout << "simple: " << test_cd(path+"1_3-1_3_random.txt", *cds[2]) << endl;
	cout << "stack: " << test_cd(path+"1_3-1_3_random.txt", *cds[3]) << endl;
 	profile_cds(path+"1_3-1_3_random.txt", "var/Report_files/1_3-1_3_random.txt", cds, names);
 	cout << "after profile cds" << endl;
 	std::vector<std::string> paths = {path+"5_3-1_3_random.txt", path+"1_3-1_3_random.txt"};
 	profile_pfs(paths,
 		"var/Report_files/{1,5}_3-1_3.txt", cds[2], {"size:5000 random", "size:1000 random"});
 	cout << "before deleteing" << endl;
 	for (auto cd : cds)
 		delete cd;
}


