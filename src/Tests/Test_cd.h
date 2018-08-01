/*
*	Interface for the testing of correctnes of choice dictionaries.
*	Single Responsibility: check if choice dictionary correct.
*
*	Created by Felix Hafner, 05.06.18
*/

#ifndef TEST_CD_H
#define TEST_CD_H

#include "Core/Choice_dictionary/Choice_dictionary.h"
#include "Profiling/Profiling_file.h"
#include <string>

bool test_choice_dictionary(const Profiling_file& pf, Choice_dictionary& cd);
std::vector<bool> test_choice_dictionaries(const std::string path, std::vector<Choice_dictionary>& cds);

#endif //TEST_CD_H
