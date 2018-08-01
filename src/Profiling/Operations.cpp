/*
*	
*
*	Created by Felix Hafner, 31.05.18
*/

#include "Operations.h"
#include <utility>
#include <iostream>
#include <cassert>


std::istream& operator>>(std::istream& is, cd_operations& o) {
	std::string operation_string;
	is >> operation_string;
	if (operation_string == "insert")
		o = cd_operations::insert;
	else if (operation_string == "delete" ||operation_string == "del")
		o = cd_operations::del;
	else if (operation_string == "contains")
		o = cd_operations::contains;
	else if (operation_string == "choice")
		o = cd_operations::choice;
	return is;
}


std::ostream& operator<<(std::ostream& os, const cd_operations& o) {
	if (o == cd_operations::insert)
		os << "insert";
	else if (o == cd_operations::del)
		os << "delete";
	else if (o == cd_operations::contains)
		os << "contains";
	else if (o == cd_operations::choice)
		os << "choice";
	return os;
}


std::string op_to_str(cd_operations o) {
	switch (o) {
		case (cd_operations::insert):
			return "insert";
		case (cd_operations::del):
			return "delete";
		case (cd_operations::contains):
			return "contains";
		case (cd_operations::choice):
			return "choice";
		default:
			return "not implemented yet";
	}
}


cd_operations str_to_op(std::string o) {
	assert(o == "insert" || o == "delete" || o == "del" || o == "contains" || o == "choice");

	if (o == "insert")
		return cd_operations::insert;
	else if (o == "delete" || o == "del")
		return cd_operations::del;
	else if (o == "contains")
		return cd_operations::contains;
	else						// only choice possible.
		return cd_operations::choice;
}