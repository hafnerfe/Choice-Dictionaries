/*
*	Operations for a Choice Dictionary.
*
*	Created by Felix Hafner, 31.05.18
*/

#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <string>

// Enumeration of the operations available for a Choice Dictionary
enum class cd_operations {
	insert,
	del,
	contains,
	choice
};


std::istream& operator>>(std::istream& is, cd_operations& o);
std::ostream& operator<<(std::ostream& os, const cd_operations& o);

std::string op_to_str(cd_operations o);
cd_operations str_to_op(std::string o);

#endif //OPERATIONS_H
