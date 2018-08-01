
CC=g++
CFLAGS= -std=c++14 -Wall -Wextra -stdlib=libc++ -Isrc -O3
O_PTH=Objects/
OBJECTS = $(O_PTH)find_one_collection.o $(O_PTH)main.o \
	$(O_PTH)profile_fo.o $(O_PTH)rng.o

main: $(OBJECTS)
	$(CC) $(OBJECTS) $(CFLAGS)

$(O_PTH)rng.o: src/rng.cpp src/rng.h
	$(CC) -c src/rng.cpp -o $(O_PTH)rng.o $(CFLAGS)

$(O_PTH)main.o: main.cpp $(O_PTH)profile_fo.o $(O_PTH)rng.o
	$(CC) -c main.cpp -o $(O_PTH)main.o $(CFLAGS)

$(O_PTH)profile_fo.o: src/profile_fo.cpp src/profile_fo.h $(O_PTH)rng.o \
	$(O_PTH)find_one_collection.o
	$(CC) -c src/profile_fo.cpp -o $(O_PTH)profile_fo.o $(CFLAGS)

$(O_PTH)find_one_collection.o: src/find_one_collection.cpp src/find_one_collection.h
	$(CC) -c src/find_one_collection.cpp -o $(O_PTH)find_one_collection.o $(CFLAGS)


.PHONY: clean
clean: 
	-rm $(OBJECTS) a.out