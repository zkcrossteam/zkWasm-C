#ifndef __ZKWASM_BN254__

#define __ZKWASM_BN254__

#include <stdbool.h>
#include <zkwasmsdk.h>

void bn254pair_g1(uint64_t x);
void bn254pair_g2(uint64_t x);
uint64_t bn254pair_pop(void);

void bn254msm_g1(uint64_t x);
uint64_t bn254msm_pop(void);

void bn254pair(uint64_t* g1, uint64_t* g2, uint64_t* g3);
void bn254msm(uint32_t size, uint64_t* g1, uint64_t *gr);

#endif
