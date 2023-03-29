#ifndef __ZKWASM_BLS__

#define __ZKWASM_BLS__

#include <stdbool.h>
#include <zkwasmsdk.h>

void blspair_g1(uint64_t x);
void blspair_g2(uint64_t x);
uint64_t blspair_pop(void);

void blssum_g1(uint64_t x);
uint64_t blssum_pop(void);

void blspair(uint64_t* g1, uint64_t* g2, uint64_t* g3);
void blssum(uint32_t size, uint64_t* g1, uint64_t *gr);

#endif
