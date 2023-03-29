#include "bls.h"

#define LIMBSZ 8

void blspair(uint64_t* g1, uint64_t* g2, uint64_t* g3) {
    int i;
    for(i=0;i<(LIMBSZ * 2 + 1);i++) {
        blspair_g1(g1[i]);
    }
    for(i=0;i<(LIMBSZ * 4 + 1);i++) {
        blspair_g2(g2[i]);
    }
    for(i=0;i<(LIMBSZ * 12);i++) {
        g3[i] = blspair_pop();
    }
}

void blssum(uint32_t size, uint64_t* g1, uint64_t *gr) {
    int i, j;
    for (i=0; i<size; i++) {
        for(j=0; j<(LIMBSZ * 2 + 1); j++) {
            blssum_g1(g1[i*17+j]);
        }
    }
    for(i=0; i<(LIMBSZ * 2 + 1); i++) {
        gr[i] = blssum_pop();
    }
}
