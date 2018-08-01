/*
*	Random number Generator.
*/

#ifndef RNG_H
#define RNG_H
#define RNG_MAX 65535

#include <stdint.h>


uint16_t rng();
void srng(uint32_t seed=1);

template <class T>
T get_random_number(T max) {
	T random_number=0;
	for (uint16_t i=0; i < sizeof(T)*8; i+=16)
		random_number |= (rng()<<i);
	return random_number%max;
}

template <class T>
T get_random_number(double set_bit_probability) {
	// Each bit has set_bit_probability of being set.
	T random_number=0;
	for (uint16_t i = 0; i < sizeof(T)*8; ++i) {
		random_number |= (((int)(rng()/(double)RNG_MAX+set_bit_probability))<<i);
	}
	return random_number;
}

#endif // RNG_H