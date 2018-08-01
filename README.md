# An Optimal Choice Dictionary

Informally, a Choice Dictionary is a bit vector with two additional operations: Initialisation (i.e. the clearing of all bits) and Choice, which returns the position of a set bit.

This program lets you use an efficient implementation of a Choice Dictionary (invented by T. Hagerup) or create your own implementation and conveniently compare it with others.

## Installation

To install this program, simply download it, and run 'make'.
This should create two archive files, which you can link at compile time.
To use the functions provided by this program, simple #include "src/cd_dev.h" or #include "src/cd.h"
You will also need to link the archive file when compiling.


## Available Functions for users:

The following functions (declared in "cd.h") are provided for people who want to use the Datastructure.

Class cd:

### Constructor:
cd(uint64_t n):
initializes the Choice dictionary

cd(uint64_t n, std::vector<uint64_t> init_list):
initializes the Choice dictionary with values in init_list

### Member functions:

void insert(uint64_t i)
inserts i into the Choice Dictionary

void del(uint64_t i)
deletes i from the Choice Dictionary

uint64_t choice()
returns the position of some element in the Choice Dictionary

bool contains(_t::len_t i)
returns true, iff i is in the Choice Dictionary.


## Available Functions for creators:



### Creating a Choice Dictionary with several modes.
enum class cd_modes {def, small, dense, sparse};
Choice_dictionary* create_choice_dictionary(
		uint64_t universe_size, 
		cd_modes mode = cd_modes::def);
Will return a pointer to a chosen choice dictionary of specified size.


### Creating a certain Datastructure.
enum class cd_implementations{small, optimal, simple, stack};
Choice_dictionary* create_choice_dictionary(
		uint64_t universe_size, 
		cd_implementations implementation);
Will return a pointer to a specified choice dictionary with specified size.


### Profiling several Choice Dictionaries on one Profiling File.
void profile_cds(
		const std::string& src_path, 
		const std::string& dst_path, 
		std::vector<Choice_dictionary*> cds, 
		const std::vector<std::string>& names);
Will profile several choice dictionaries. src_path is the path of the Profiling File.
dst_path is where the Report File will be saved. names is needed for the Report File.
Each Choice Dictionary is named, so names.size() == names.size().

void profile_cds(
		const Profiling_file& pf, 
		const std::string& dst_path, 
		std::vector<Choice_dictionary*> cds, 
		const std::vector<std::string>& names);
Same as above but with Profiling_file already loaded.
Will be beneficial for large operation sizes that are not saved.


### Profiling several Profiling Files using one Choice Dictionary.
void profile_pfs(
		const std::vector<std::string>& src_paths, 
		const std::string& dst_path, 
		Choice_dictionary* cd, 
		const std::vector<std::string>& names);
Will profile several Profiling Files using just one Choice Dictionary.
src_paths specifies the path of the Profiling Files.
Each Profiling File is named, so names.size()==src_paths.size().

void profile_pfs(
		const std::vector<Profiling_file>& pfs, 
		const std::string& dst_path, 
		Choice_dictionary* cd, 
		const std::vector<std::string>& names);
Same as above but with the Profiling Files already loaded.

### Testing the correctness of a Datastructure with a Profiling File.
bool test_cd(std::string src_path, Choice_dictionary& cd);
Will run the Choice Dictionary on a Profiling File (specified by src_path) and check if 
the resulting state is correct.

### Creating random operations (with probabilities).
std::vector<std::pair<std::string, _t::len_t> > create_random_operations(
		uint64_t operation_count,
		_t::len_t maximum_size,
		const std::vector<std::string>& operations_s 
			= {"insert", "del", "contains", "choice"},
		const std::vector<double>& probabilities 
			= {0.25, 0.25, 0.25, 0.25});
Simply returns a random input (i.e. a sequence of operations and arguments).
The Probabilities of each operation can be chosen, and operations can be omitted.


### The Class Profiling_file.

Constructors and Deconstructor:
Profiling_file();
Profiling_file(const std::string& path);
~Profiling_file();

void save(const std::string& path);

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

void set_init_operations(const input_t& init_operations);
void add_init_operations(const std::vector<std::pair<std::string ,uint64_t> >& init_operations);
void add_init_operation(const operation_pair_t& op);
void add_init_operation(const std::string& operation_s, uint64_t arg);
input_ptr get_init_operations() const;

void set_profiling_operations(const input_t& profiling_operations);
void add_profiling_operations(const std::vector<std::pair<std::string, uint64_t> >& profiling_operations);
void add_profiling_operation(const operation_pair_t& op);
void add_profiling_operation(const std::string& operation_s, uint64_t arg);
		input_ptr get_profiling_operations() const;
