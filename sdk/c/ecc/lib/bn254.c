#include "bn254.h"

#define LIMBSZ 6

void bn254pair(uint64_t* g1, uint64_t* g2, uint64_t* g3) {
    int i;
    for(i=0;i<(LIMBSZ * 2 + 1);i++) {
        bn254pair_g1(g1[i]);
    }
    for(i=0;i<(LIMBSZ * 4 + 1);i++) {
        bn254pair_g2(g2[i]);
    }
    for(i=0;i<(LIMBSZ * 12);i++) {
        g3[i] = bn254pair_pop();
    }
}

#define MSMLIMB (LIMBSZ*2+1+4)

void bn254msm(uint32_t size, uint64_t* g1, uint64_t *gr) {
    int i, j;
    for (i=0; i<size; i++) {
        // prepare point and scalar
        for(j=0; j<(LIMBSZ * 2 + 1 + 4); j++) {
            bn254msm_g1(g1[MSMLIMB*i+j]);
        }
    }
    for(i=0; i<(LIMBSZ * 2 + 1); i++) {
        gr[i] = bn254msm_pop();
    }
}
