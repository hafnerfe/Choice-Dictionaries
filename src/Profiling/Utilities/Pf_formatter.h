/*
*	This is a Helper Interface for some String operations that are used by Profiling_file.h.
*
* 	Created by Felix Hafner, 24.06.18
*/

#ifndef PF_FORMATTER_H
#define PF_FORMATTER_H

#include <string>
#include <cstdint>
#include <vector>
#include "Profiling/Operations.h"


/*
*	Defines a string used for visual separation.
*/
std::string get_separator();

/*
*	Reads out (and ignores) n lines out of is.
*/
void dismiss_n_lines(int n, std::istream& is);

/*
*	Reads lines out of is until the separator line.
*	After the operation is is at line after the separator.
*/
void dismiss_until_separator(std::istream& is);

/*
*	Returns the string in the current line after the first colon.
*	Also removes any leading whitespaces.
*/
std::string read_string_after_colon(std::istream& is);

/*
*	Reads in all Operations from is and returns Operations and Arguments in a Vector.
*	Assumes that istream is on a blank line, followed by Operations, and that Operations and 
*	Arguments are seperated by a new line.
*/
std::vector<std::pair<cd_operations, uint64_t> > read_operations(std::istream& is);

/*
*	Writes the operations, ending with a separator line. Must be readable by "read_operations".
*/
void write_operations(std::ostream& os, std::vector<std::pair<cd_operations, uint64_t> > operations);

#endif // PF_FORMATTER_H
