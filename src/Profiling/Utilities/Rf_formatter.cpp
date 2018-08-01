/*
*
*
*	Created by Felix Hafner, 24.06.18
*/

#include "Rf_formatter.h"
#include <fstream>
#include <cmath>
#include <numeric>
#include <cassert>


double compute_mean(const std::vector<double>& v) {
	double sum = std::accumulate(v.begin(), v.end(), 0.0);
	return sum / v.size();
}

double compute_stdev(const std::vector<double>& v) {
	double mean = compute_mean(v);
	double sq_sum = std::inner_product(
			v.begin(), v.end(), v.begin(), 0.0);
	return std::sqrt(sq_sum / v.size() - mean * mean);
}

double compute_min(const std::vector<double>& v) {
	return *min_element(v.begin(), v.end());
}

double compute_max(const std::vector<double>& v) {
	return *max_element(v.begin(), v.end());
}


void write_statistics(
		const std::vector<std::string>& names,
		const std::vector<std::vector<double> >& results,
		std::ostream& os) {

	assert(names.size() == results.size());

	for (unsigned int i = 0; i < names.size(); ++i) {
		auto name = names[i];
		auto result = results[i];
		os << "Name: " << names[i] << '\n';
		os << "mean: " << compute_mean(result) << '\n';
		os << "stdev: " << compute_stdev(result) << '\n';
		os << "min: " << compute_min(result) << '\n';
		os << "max: " << compute_max(result) << '\n';
		os << "---" << "\n\n";
	}
}

