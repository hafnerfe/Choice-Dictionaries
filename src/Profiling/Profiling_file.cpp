/*
*	Profiling File Source Code
*
*	Created on 31.05.18 by Felix Hafner
*/

#include "Profiling_file.h"
#include "Utilities/Pf_formatter.h"
#include <iostream> 			// Only included for <<endl; might be removed later.
#include <fstream>
#include <ctime>
#include <sstream>
#include <cassert>


Profiling_file::Profiling_file() :
  		save_operations_f(true),
		init_operations(std::make_shared<input_t>()),
  		profiling_operations(std::make_shared<input_t>()){
}


Profiling_file::Profiling_file(const std::string& path) {
	/*
	*	Will load a Profiling_file from specified path. (Path must be valid)
	*	Also automatically sets the path of the Profiling_file.
	*/

	std::ifstream file (path);
	assert(file.is_open());
    file >> *this;
    file.close();
  	set_path(path);
}


Profiling_file::~Profiling_file() {
	/*
	*	Deconstructor.
	*	Responsibility: delete all used memory. Leave no space leaks.
	*	Shared Pointer will delete itself.
	*	Thus, no work has to be done.
	*/

}


void Profiling_file::save(const std::string& path) {
	/*
	*	Saves a Profiling_file at specifed path.
	*	Will add the given path as attribute to the Profiling_file (before saving!)
	*/

	this->path=path;
	// If date has not been set yet, set it to now:
	if (this->date.empty())
		this->set_date();

	std::ofstream file(path);
	assert(file.is_open());
	file << *this;
	file.close();
}


void Profiling_file::save_operations(bool b) { this->save_operations_f=b; }

bool Profiling_file::save_operations() const { return this->save_operations_f; }


void Profiling_file::set_date() {
	/*
	*	Sets the date of the Profiling_file to now.
	*/

	time_t now = time(0);
	date=ctime(&now);

	// erase all newlines at end of date: (should only be one)
	while (!date.empty() && date[date.length()-1] == '\n')
		date.erase(date.length()-1);
	this->set_date(date);
}


void Profiling_file::set_date(const std::string& date) {
	this->date=date;
}


std::string Profiling_file::get_date() const{
	return this->date;
}


void Profiling_file::set_name(const std::string& name) {
	this->name=name;
}


std::string Profiling_file::get_name() const {
	return this->name;
}


void Profiling_file::set_path(const std::string& path) {
	this->path=path;
}


std::string Profiling_file::get_path() const{
	return this->path;
}


void Profiling_file::set_max_argument_size(uint64_t arg) {
	this->max_argument_size = arg;
}


uint64_t Profiling_file::get_max_argument_size() const{
	return this->max_argument_size;
}


void Profiling_file::set_information(const std::vector<std::string>& information) {
	this->information = information;
}


std::vector<std::string> Profiling_file::get_information() const{
	return this->information;
}


void Profiling_file::add_information(const std::string& i) {
	std::vector<std::string> info = this->get_information();
	info.push_back(i);
	this->set_information(info);
}


void Profiling_file::set_init_operations(const input_t& init_operations) {
	this->init_operations = std::make_shared<input_t>(init_operations);
}


void Profiling_file::add_init_operations(const std::vector<std::pair<std::string ,uint64_t> >& init_operations) {
	for (auto o : init_operations)
		this->add_init_operation(o.first, o.second);
}


void Profiling_file::add_init_operation(const std::pair<cd_operations,uint64_t>& op) {
	/*
	*	Will ad the pair to the init_operations.
	*	Uses get_init_operations and set_init_operations.
	*/
	
	this->init_operations->push_back(op);
}


void Profiling_file::add_init_operation(const std::string& operation_s, uint64_t arg) {
	/*
	*	Will add the operation_s ("insert", "delete", "choice", "contains") and the argument to init_operations.
	*	Uses add_init_operation(std::pair<cd_operations,uint64_t>op)
	*		-> Uses get_init_operations and set_init_operations.
	*/

	cd_operations operation = str_to_op(operation_s);
	this->add_init_operation(std::make_pair(operation, arg));
}


input_ptr Profiling_file::get_init_operations() const{
	return this->init_operations;
}


void Profiling_file::set_profiling_operations(const input_t& profiling_operations) {
	this->profiling_operations = std::make_shared<input_t>(profiling_operations);
}


void Profiling_file::add_profiling_operations(const std::vector<std::pair<std::string, uint64_t> >& profiling_operations) {

	for (auto o : profiling_operations) 
		this->add_profiling_operation(o.first, o.second);
}


void Profiling_file::add_profiling_operation(const operation_pair_t& op) {
	/*
	*	Will ad the pair to the profiling_operations.
	*	Uses get_profiling_operations and set_profiling_operations.
	*/
	
	this->profiling_operations->push_back(op);
}


void Profiling_file::add_profiling_operation(const std::string& operation_s, uint64_t arg) {
	/*
	*	Will add the operation_s ("insert", "delete", "choice", "contains") and the argument to profiling_operations.
	*	Uses add_profiling_operation(std::pair<cd_operations,uint64_t>op)
	*		-> Uses get_profiling_operations and set_profiling_operations.
	*/

	cd_operations operation = str_to_op(operation_s);
	this->add_profiling_operation(std::make_pair(operation, arg));
}


input_ptr Profiling_file::get_profiling_operations() const{
	return this->profiling_operations;
}





std::istream& operator>>(std::istream& is, Profiling_file& pf) {
	/*
	*	Reads in a Profiling_file from istream. 
	*	Reads in block after block.
	*/
	

	std::string line;

	// 1st Block:	Comments, can be ignored
	dismiss_until_separator(is);

	// 2nd Block: 	Information.
	dismiss_n_lines(1,is);
	pf.set_path(read_string_after_colon(is));
	pf.set_name(read_string_after_colon(is));
	pf.set_date(read_string_after_colon(is));

	dismiss_n_lines(3, is);

	pf.save_operations(read_string_after_colon(is) == "1"?true:false);
	pf.set_max_argument_size(stoll(read_string_after_colon(is)));
	
	dismiss_n_lines(2, is);

	auto info = pf.get_information();
	while (getline(is, line)) {				// Additional Information
		if (line == get_separator())
			break;
		info.push_back(line);
	}
	pf.set_information(info);

	if (!pf.save_operations()) {
		
		return is;
	}

	// 3rd Block: Default Operations
	dismiss_n_lines(2,is);
	pf.set_init_operations(read_operations(is));

	// 4th Block: Profiling Operations.
	dismiss_n_lines(2,is);
	pf.set_profiling_operations(read_operations(is));
	return is;
}


std::ostream& operator<<(std::ostream& os, const Profiling_file& pf) {
	/*
	*	Writes the Profiling_file in ostream.
	*	Operation is split up in blocks.
	*/

	using namespace std;
	std::string separator = get_separator();

	// Block 1: Comments
	os << "# This is a Profiling File. It was generated automatically.\n";
	os << "# For more information please look into /src/Profiling/ProfilingFile.*\n";
	os << separator << "\n\n";

	// Block 2: Information
	os << "Path: " << pf.get_path() << endl;
	os << "Name: " << pf.get_name() << endl;
	os << "Date: " << pf.get_date() << endl << endl;
	
	os << "Number of Default Operations: " << pf.get_init_operations()->size() << endl;
	os << "Number of Profiling Operations: " << pf.get_profiling_operations()->size() << endl;
	os << "Saving the Operations in this file: " << pf.save_operations() << endl;
	os << "Maximum argument size: " << pf.get_max_argument_size() << endl << endl;
	os << "Additional Information:" << endl;

	for (auto i : pf.get_information())
		os << i << endl;
	os << separator << "\n\n";

	// Block 3: 
	os << "Default Operations:" << endl;
	if (pf.save_operations())
		write_operations(os, *(pf.get_init_operations()));
	os << "\n\n";

	// Block 4:
	os << "Profiling Operations:" << endl;
	if (pf.save_operations())
		write_operations(os, *(pf.get_profiling_operations()));
	os << "\n\n";

	return os;
}



