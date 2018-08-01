/*
*	Rf (= Report File) Formatter.
*	Used for writing the statistics in an ostream.
*
*	Created by Felix Hafner, 24.06.18
*/

#ifndef RF_FORMATTER_H
#define RF_FORMATTER_H

#include <vector>
#include <string>


void write_statistics(
	const std::vector<std::string>& names,
	const std::vector<std::vector<double> >& results,
	std::ostream& os);


#endif // RF_FORMATTER_H




