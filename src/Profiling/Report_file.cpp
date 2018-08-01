/*
*	Report File Source Code
*
*	Created on 31.05.18 by Felix Hafner
*/

#include "Report_file.h"
#include "Utilities/Pf_formatter.h"
#include "Utilities/Rf_formatter.h"
#include <iostream>	//Only included for << endl;
#include <fstream>
#include <ctime>



void Report_file::save(std::string path) {
	this->set_path(path);
	std::ofstream file (path);
  	if (file.is_open()) {
    	file << *this;
    	file.close();
  	}
  	else {
  		//Throw an Excpetion?
  	}
}


Profiling_file Report_file::get_profiling_file() const {
	return this->pf;
}


void Report_file::set_profiling_file(const Profiling_file& pf) {
	this->pf = pf;
}


std::string Report_file::get_path() const {
	return this->path;
}


void Report_file::set_path(const std::string& path) {
	this->path = path;
}


std::string Report_file::get_date() const {
	return this->date;
}


void Report_file::set_date() {
	/*
	*	Sets the date of the Report_file to now.
	*/

	time_t now = time(0);
	date=ctime(&now);

	// erase all newlines at end of date: (should only be one)
	while (!date.empty() && date[date.length()-1] == '\n')
		date.erase(date.length()-1);
	this->set_date(date);
}


void Report_file::set_date(const std::string& date) {
	this->date = date;
}


uint16_t Report_file::get_repetition_count() const {
	return this->repetition_count;
}

void Report_file::set_repetition_count(uint16_t repetition_count) {
	this->repetition_count = repetition_count;
}


std::vector<std::string> Report_file::get_information() const {
	return this->information;
}


void Report_file::set_information(const std::vector<std::string>& info) {
	this->information=info;
}


void Report_file::add_information(const std::string& info) {
	auto info_vector = this->get_information();
	info_vector.push_back(info);
	this->set_information(info_vector);
}


std::vector<std::string> Report_file::get_names() const {
	return this->names;
}


void Report_file::set_names(const std::vector<std::string>& names) {
	this->names=names;
}


void Report_file::add_name(const std::string& name){
	auto name_vector = this->get_names();
	name_vector.push_back(name);
	this->set_names(name_vector);
}


std::vector<std::vector<double> > Report_file::get_results() const {
	return this->results;
}


void Report_file::set_results(const std::vector<std::vector<double> >& results) {
	this->results=results;
}


void Report_file::add_result(const std::vector<double>& result) {
	auto results_vector = this->get_results();
	results_vector.push_back(result);
	this->set_results(results_vector);
}



std::ostream& operator<<(std::ostream& os, const Report_file& rf) {
	using namespace std;

	// Block 1: Info about Report File
	os << "This is a Report File." << endl;
	os << "Date: " << rf.get_date() << endl;
	os << "Path: " << rf.get_path() << endl;
	os << "Number of repetitions: " << rf.get_repetition_count() << endl << endl;
	os << "Report file info: " << endl;
	for (auto i : rf.get_information())
		os << i << endl;

	Profiling_file pf = rf.get_profiling_file();
	// Block 2: Info about Profiling File
	os << get_separator() << endl << endl;
	os << "Path of Profiling File: " << pf.get_path() << endl;
	os << "Name of Profiling File: " << pf.get_name() << endl;
	os << "Date of Profiling File: " << pf.get_date() << endl << endl;
	os << "Number of Initialization Operations: " << pf.get_init_operations()->size() << endl;
	os << "Number of Profiling Operations: " << pf.get_profiling_operations()->size() << endl;
	os << "Max Argument Size: " << pf.get_max_argument_size() << endl << endl;
	os << "Profiling file info:" << endl;
	for (auto i : pf.get_information())
		os << i << endl;

	// Block 3: Info about results
	os << get_separator() << endl << endl;
	os << "Results." << endl << endl;
	
	write_statistics(rf.get_names(), rf.get_results(), os);
	return os;
}