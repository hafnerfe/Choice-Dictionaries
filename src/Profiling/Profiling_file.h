/*
*	Profiling File Header
*	Declaration of the class Profiling File
*	Functions to save and load a Profiling File
*
*	Created on 31.05.18 by Felix Hafner
*/

#ifndef PROFILING_FILE_H
#define PROFILING_FILE_H


#include <string>
#include <cstdint>
#include <vector>
#include <memory>
#include <utility>
#include "Operations.h"


typedef std::pair<cd_operations, uint64_t> operation_pair_t;
typedef std::vector<operation_pair_t> input_t;
typedef std::shared_ptr<input_t> input_ptr;		// Shared for getters.

struct Profiling_file {
	/* 	
	*	A Profoling File is created to benchmark Choice Dictionaries.
	* 	It contains a name, a date, the number of operations, the max argument size,
	* 	some additional information, and the operations as a pair of operation and argument
	* 	Operations are seperated: default_operations and profiling_operations.
	* 	init_operations are executed before profiling. They can e.g. be used
	* 	to fill up the Choice Dictionary.
	* 	profiling_operations are those that will be profiled.
	*
	*	The profiling file can be saved to a readable form (and also be loaded).
	*
	*	The input for a datastructure is a list of operations and arguments that are
	*	executed in order.
	*	Thus, input_t is a vecotr of pairs of operation_types and arguments.
	*	input_ptr is a pointer to input_t (usually a smart pointer)
	*/

	
	private:
		std::string name;
		std::string path;					// where file will be saved. Will be set automatically
		std::string date;
		uint64_t max_argument_size;			// biggest argument size.
		std::vector<std::string> information;
		bool save_operations_f;				// when set, saves all operations in the specified file.
		input_ptr init_operations;			// operations that will not be profiled.
		input_ptr profiling_operations;		// operations that will be profiled.


	public:

		/*
		*	Constructor: 
		*	If given a path as parameter, the Profiling File will form that path will be loaded.
		*/
		Profiling_file();
		Profiling_file(const std::string& path);
		~Profiling_file();


		// Copy operator: Default suffices.
		//Profiling_file& operator=(const Profiling_file& other);

		/*
		*	Saves the Profiling File at specified path.
		*	The Saved File aims at being readable.
		*	The related read operation is hidden in the Constructor.
		*/
		void save(const std::string& path);

		// Getter and Setter:

		void save_operations(bool b);
		bool save_operations() const;

		void set_date();
		void set_date(const std::string& date);
		std::string get_date() const;

		void set_name(const std::string& name);
		std::string get_name() const;

		void set_path(const std::string& path);
		std::string get_path() const;

		void set_max_argument_size(uint64_t arg);
		uint64_t get_max_argument_size() const;

		void set_information(const std::vector<std::string>& information);
		void add_information(const std::string& i);
		std::vector<std::string> get_information() const;


		/*
		*	Init Operations: 	Operations that are executed before the profiling operations.
		*						They will not be profiled and can be used to fill up the CD.
		*	cd_operations is defined in "Operations.h".
		*	For beginners, only the operation "add_init_operations(std::string operation_s, uint64_t arg);"
		*	is needed. Operation_s can be either "insert", "delete", "contains", or "choice".
		*	Typos will result in undefined behaviour. 
		*/
		void set_init_operations(const input_t& init_operations);
		void add_init_operations(const std::vector<std::pair<std::string ,uint64_t> >& init_operations);
		void add_init_operation(const operation_pair_t& op);
		void add_init_operation(const std::string& operation_s, uint64_t arg);
		input_ptr get_init_operations() const;


		/*
		*	Profiling Operations: 	Operations that will be profiled.
		*							
		*	cd_operations is defined in "Operations.h".
		*	For beginners, only the operation "add_profiling_operations(std::string operation_s, uint64_t arg);"
		*	is needed. Operation_s can be either "insert", "delete", "contains", or "choice".
		*	Typos will result in undefined behaviour. 
		*/
		void set_profiling_operations(const input_t& profiling_operations);
		void add_profiling_operations(const std::vector<std::pair<std::string, uint64_t> >& profiling_operations);
		void add_profiling_operation(const operation_pair_t& op);
		void add_profiling_operation(const std::string& operation_s, uint64_t arg);
		input_ptr get_profiling_operations() const;

};




std::istream& operator>>(std::istream& is, Profiling_file& pf);	
std::ostream& operator<<(std::ostream& os, const Profiling_file& pf);


#endif //PROFILING_FILE_H
