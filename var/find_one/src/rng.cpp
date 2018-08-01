#include "rng.h"


static uint32_t rng_next = 0;

uint16_t rng() {
	rng_next= (rng_next * 1103515245U + 12345U) & 0x7fffffffU;
	
	
	return (uint16_t)rng_next;
}
void srng(uint32_t seed) {rng_next=seed&0x7fffffffU;}
