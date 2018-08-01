/*
*	Report File Header
*	Declaration of the class Report_file
*	Functions to save a report file and to compute result statistics
*	
*	Created on 31.05.18 by Felix Hafner
*/

#ifndef REPORTFILE_H
#define REPORTFILE_H


#include "Profiling_file.h"
#include <string>
#include <vector>
#include "Operations.h"


struct Report_file {
	/*
	* 	A Report File is created after Choice Dictionaries have been profiled.
	* 	Report File contains the Profiling File that was used to profile,
	* 	a date, more info, the names of the Choice Dictionaries, and the results.
	* 	It can also be used as a report for the profiling of Profiling Files.
	* 	Then cd_names represents the different Profiling Files
	*/
	private:
		Profiling_file pf;
		std::string path;
		std::string date;
		uint16_t repetition_count;
		std::vector<std::string> information;
		std::vector<std::string> names;				// must match the results
		std::vector<std::vector<double> > results;

	public:
		
		// Constructor:
		Report_file() = default;

		void save(std::string path);

		// Getter and Setter:

		Profiling_file get_profiling_file() const;
		void set_profiling_file(const Profiling_file& pf);

		std::string get_path() const;
		void set_path(const std::string& path);

		std::string get_date() const;
		void set_date();
		void set_date(const std::string& date);

		uint16_t get_repetition_count() const;
		void set_repetition_count(uint16_t repetition_count);

		std::vector<std::string> get_information() const;
		void set_information(const std::vector<std::string>& info);
		void add_information(const std::string& info);

		std::vector<std::string> get_names() const;
		void set_names(const std::vector<std::string>& names);
		void add_name(const std::string& name);

		std::vector<std::vector<double> > get_results() const;
		void set_results(const std::vector<std::vector<double> >& results);
		void add_result(const std::vector<double>& result);
};



/*
*	Function to write a report file into ostream. 
*	There is no need to read in a report file.
*/
std::ostream& operator<<(std::ostream& os, const Report_file& rf);


#endif //REPORTFILE_H
