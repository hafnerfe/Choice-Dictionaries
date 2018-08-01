#ifndef FIND_ONE_COLLECTION_H_INCLUDED
#define FIND_ONE_COLLECTION_H_INCLUDED

#include <cmath>
#include <stdint.h>
#include <vector>
#include <string>

std::vector<int (*) (uint64_t)> get_implementations(
		std::vector<std::string> &implementation_names);

std::vector<int (*) (uint64_t)> get_implementations();


int binary_search(const uint64_t number);
int fortschaltung(const uint64_t number); //calculation of differences, Diferenzialrechnung
int naive_search(const uint64_t number);
int naive_search_unrolled(const uint64_t number);
int lib_log(const uint64_t number);
int twid(const uint64_t number);
int built_in(const uint64_t number);
int dummy_find_one(const uint64_t number); //doesn't do anything
int fusion_trees(const uint64_t number);

#endif
