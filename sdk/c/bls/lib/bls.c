#include "bls.h"
void blspair(uint64_t* g1, uint64_t* g2, uint64_t* g3) {
    int i;
    for(i=0;i<17;i++) {
        blspair_g1(g1[i]);
    }
    for(i=0;i<33;i++) {
        blspair_g2(g1[i]);
    }
    for(i=0;i<48;i++) {
        g3[i] = blspair_pop();
    }
}

void blssum(uint32_t size, uint64_t* g1, uint64_t *gr) {
    int i;
    for (i=0; i<size; i++) {
        for(i=0;i<17;i++) {
            blssum_g1(g1[i]);
        }
    }
    for(i=0;i<17;i++) {
        gr[i] = blssum_pop();
    }
}
