#include "bn254.h"

#define LIMBSZ 5

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
        bn254_sum_new(i==0);
        for(j=0; j<4; j++) {
            bn254_sum_scalar(g1[MSMLIMB*i+j]);
        }
        for(j=4; j<(LIMBSZ * 2 + 1 + 4); j++) {
            bn254_sum_g1(g1[MSMLIMB*i+j]);
        }
        for(i=0; i<(LIMBSZ * 2 + 1); i++) {
            gr[i] = bn254_sum_finalize();
        }
    }
}
