CC = g++
CFLAGS=-std=c++14 -Wall -Wextra -stdlib=libc++ -Isrc/ -O3

OBJECT_PTH=src/Object_files/
CORE_PTH=src/Core/
CD_PTH=$(CORE_PTH)Choice_dictionary/

objects_eval = $(OBJECT_PTH)cd_dev.o $(OBJECT_PTH)Test_cd.o $(OBJECT_PTH)rng.o\
	$(OBJECT_PTH)Operations.o $(OBJECT_PTH)Profiler.o $(OBJECT_PTH)Profiling_file.o $(OBJECT_PTH)Report_file.o \
	$(OBJECT_PTH)Pf_formatter.o $(OBJECT_PTH)Rf_formatter.o $(OBJECT_PTH)Bit_opteraionts.o \
	$(OBJECT_PTH)Optimal_cd.o $(OBJECT_PTH)Simple_cd.o $(OBJECT_PTH)Small_cd.o $(OBJECT_PTH)Stack_cd.o 
	

objects_cd = $(OBJECT_PTH)Optimal_cd.o $(OBJECT_PTH)Simple_cd.o $(OBJECT_PTH)Small_cd.o \
	$(OBJECT_PTH)Stack_cd.o  $(OBJECT_PTH)cd.o

CD=$(CD_PTH)Choice_dictionary.h 
CA=src/Core/Choice_array/Choice_array.h
O_CD_h=$(CD_PTH)Optimal_cd.h
PF_h=src/Profiling/Profiling_file.h
RF_h=src/Profiling/Report_file.h
SI_CD_h=$(CD_PTH)Simple_cd.h
SM_CD_h=$(CD_PTH)Small_cd.h
ST_CD_h=$(CD_PTH)Stack_cd.h
O_CA_h=src/Core/Choice_array/Optimal_ca.h src/Core/Choice_array/Optimal_ca.cpp
OPS_h=src/Profiling/Operations.h
RF_F_h=src/Profiling/Utilities/Rf_formatter.h
PF_F_h=src/Profiling/Utilities/Pf_formatter.h
OPS_c=src/Profiling/Operations.cpp
TYPES_H=src/types.h
BIT_OPS_ALL=src/Core/Utilities/Bit_operations.tpp src/Core/Utilities/Bit_operations.cpp \
	src/Core/Utilities/Integer_operations.tpp





test: tests.cpp lib_cd_dev.a lib_cd.a
	$(CC) tests.cpp lib_cd_dev.a lib_cd.a -o tests $(CFLAGS)


lib_cd.a: $(objects_cd)
	ar rcs lib_cd.a $(objects_cd) 

lib_cd_dev.a: $(objects_eval)
	ar rcs lib_cd_dev.a $(objects_eval)

# Facades:

$(OBJECT_PTH)cd_dev.o: src/cd_dev.cpp src/cd_dev.h $(CD) $(CA) $(PF_h) \
		$(O_CD_h) $(SI_CD_h) $(SM_CD_h) $(ST_CD_h) $(O_CA_h) \
		src/Profiling/Profiler.h $(RF_h) src/Tests/Test_cd.h $(OPS_h) \
		$(BIT_OPS_ALL) src/Profiling/Utilities/rng.cpp \
		src/Profiling/Utilities/rng.h
	$(CC) -c src/cd_dev.cpp -o $(OBJECT_PTH)cd_dev.o $(CFLAGS)

$(OBJECT_PTH)cd.o: src/cd.cpp src/cd.h $(CD) $(CA) $(O_CD_h) $(SI_CD_h) \
		$(SM_CD_h) $(ST_CD_h) $(O_CA_h) $(TYPES_H) $(BIT_OPS_ALL)
	$(CC) -c src/cd.cpp -o $(OBJECT_PTH)cd.o $(CFLAGS)

#Profiling % Testing:

$(OBJECT_PTH)Test_cd.o: src/Tests/Test_cd.cpp src/Tests/Test_cd.h $(PF_h) $(CD) $(OPS_h)
	$(CC) -c src/Tests/Test_cd.cpp -o $(OBJECT_PTH)Test_cd.o $(CFLAGS)

$(OBJECT_PTH)Operations.o: $(OPS_h) $(OPS_c) 
	$(CC) -c src/Profiling/Operations.cpp -o src/Object_files/Operations.o $(CFLAGS)

$(OBJECT_PTH)Profiler.o: src/Profiling/Profiler.h src/Profiling/Profiler.cpp $(CD) $(PF_h) $(RF_h) $(OPS_h)
	$(CC) -c src/Profiling/Profiler.cpp -o $(OBJECT_PTH)Profiler.o $(CFLAGS)

$(OBJECT_PTH)Profiling_file.o: $(PF_h) src/Profiling/Profiling_file.cpp $(OPS_h) $(PF_F_h)
	$(CC) -c src/Profiling/Profiling_file.cpp -o $(OBJECT_PTH)Profiling_file.o $(CFLAGS)

$(OBJECT_PTH)Report_file.o: $(RF_h) src/Profiling/Report_file.cpp $(PF_h) $(OPS_h) \
		src/Profiling/Utilities/Pf_formatter.h $(RF_F_h)
	$(CC) -c src/Profiling/Report_file.cpp -o $(OBJECT_PTH)Report_file.o $(CFLAGS)

$(OBJECT_PTH)Pf_formatter.o: $(PF_F_h) src/Profiling/Utilities/Pf_formatter.cpp $(OPS_h)
	$(CC) -c src/Profiling/Utilities/Pf_formatter.cpp -o $(OBJECT_PTH)Pf_formatter.o $(CFLAGS)

$(OBJECT_PTH)Rf_formatter.o: src/Profiling/Utilities/Rf_formatter.cpp $(RF_F_h)
	$(CC) -c src/Profiling/Utilities/Rf_formatter.cpp -o $(OBJECT_PTH)Rf_formatter.o $(CFLAGS)

# Choice Dictionaries:

$(OBJECT_PTH)Optimal_cd.o: $(CD_PTH)Optimal_cd.cpp $(O_CD_h)  $(BIT_OPS_ALL) \
		$(CD) $(O_CA_h) $(TYPES_H) 
	$(CC) -c src/Core/Choice_dictionary/Optimal_cd.cpp -o $(OBJECT_PTH)Optimal_cd.o $(CFLAGS)

$(OBJECT_PTH)Simple_cd.o: $(CD_PTH)Simple_cd.cpp $(SI_CD_h) $(CD) $(TYPES_H) $(BIT_OPS_ALL)
	$(CC) -c src/Core/Choice_dictionary/Simple_cd.cpp -o $(OBJECT_PTH)Simple_cd.o $(CFLAGS)

$(OBJECT_PTH)Small_cd.o: $(CD_PTH)Small_cd.cpp $(SM_CD_h) $(CD) $(TYPES_H) \
		src/Core/Utilities/Integer_operations.h $(BIT_OPS_ALL)
	$(CC) -c src/Core/Choice_dictionary/Small_cd.cpp -o $(OBJECT_PTH)Small_cd.o $(CFLAGS)

$(OBJECT_PTH)Stack_cd.o: $(CD_PTH)Stack_cd.cpp $(ST_CD_h) $(CD) $(SI_CD_h) $(TYPES_H)
	$(CC) -c src/Core/Choice_dictionary/Stack_cd.cpp -o $(OBJECT_PTH)Stack_cd.o $(CFLAGS)

$(OBJECT_PTH)Bit_opteraionts.o: $(BIT_OPS_ALL)
	$(CC) -c src/Core/Utilities/Bit_operations.cpp -o $(OBJECT_PTH)Bit_opteraionts.o $(CFLAGS)

$(OBJECT_PTH)rng.o: src/Profiling/Utilities/rng.h src/Profiling/Utilities/rng.cpp
	$(CC) -c src/Profiling/Utilities/rng.cpp -o $(OBJECT_PTH)rng.o $(CFLAGS)

.PHONY : clean
clean :
	-rm main lib_cd_dev.a lib_cd.a $(objects_eval) $(objects_cd)
