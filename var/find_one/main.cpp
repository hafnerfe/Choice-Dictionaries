#include "profile_fo.h"
#include <stdlib.h>
#include <iostream>
#include "rng.h"


using namespace std;

void test_ba_1();
void test_corr();

int main(void) {

	test_corr();
	exit(1);
	for (auto i=0; i<100; ++i) {
		cout << get_random_number((uint64_t)10000000) << endl;
	}
	//test_ba_1();
	//test_corr();	
	return 0;
}

void test_corr() {
	cout<<"incorrect implementations: "<<endl;
	auto n=get_random_numbers(1000,0.1);
	for (auto i:get_incorrect_implementations(n))
		cout<<i<<endl;
	cout<<"done."<<endl;
}

void test_ba_1() {
	// Test used for bachelor thesis.
	auto count=50000000;
	cout<<"starting first test..."<<endl;

	{
		auto n=get_random_numbers(count,0.1,237);
		profile_all(n,"test01-10p.txt");
	}
	cout<<"starting second test..."<<endl;
	{
		auto n=get_random_numbers(count,0.5,237);
		profile_all(n,"test02-50p.txt");
	}
	cout<<"starting third test..."<<endl;
	{
		auto n=get_random_numbers(count,0.9,237);
		profile_all(n,"test03-90p.txt");
	}
}