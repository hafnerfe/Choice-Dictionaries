/*
*	Source code for the Interface "Pf_formatter.h".
*
*	Created by Felix Hafner, 24.06.18
*/

#include "Pf_formatter.h"
#include <fstream>


std::string get_separator() {
	return std::string(60,'-');
}

void dismiss_n_lines(int n, std::istream& is) {
	std::string line;
	for (uint8_t i = 0; i < n; ++i) {
		std::getline(is,line);
	}
}

void dismiss_until_separator(std::istream& is) {
	std::string line;
	std::string separator = get_separator();
	while (std::getline(is,line)) {
		if (line == separator)
			return;
	}
}

std::string read_string_after_colon(std::istream& is) {
	std::string line;
	getline(is, line, ':'); 				// Before the colon
	getline(is, line);						// After the colon
	while (line.substr(0,1) == " ")			// Check if whitespace at the start
		line = line.substr(1,line.size()-1);// If so, remove it.
	return line;
}

std::vector<std::pair<cd_operations, uint64_t> > read_operations(std::istream& is) {
	std::vector<std::pair<cd_operations, uint64_t> > operations;
	std::string line;

	while (getline(is, line)) {
		if (line == get_separator())	// Check for end.
			break;
		cd_operations op;
		uint64_t arg;
		is >> op;				// Get the operation.
		dismiss_n_lines(1,is);	// Dismiss the part after the operation (isream is still in the same line).
		getline(is, line);		// Get the argument
		arg = stoll(line);		// Convert the Argument
		operations.push_back(std::make_pair(op,arg));
	}
	return operations;
}

void write_operations(std::ostream& os, std::vector<std::pair<cd_operations, uint64_t> > operations) {
	for (auto op : operations)
		os << "\n" << op.first << "\n" << op.second << "\n";
	os << get_separator();
}
