#include "hash-wasm.h"
#include "zkwasmsdk.h"

void poseidon(uint64_t* data, uint32_t size, uint64_t* r)
{
    int i,j,round;
    round = 0;
    poseidon_new(1);
    for(i=0; i<size; i++) {
        j = i*4;
        poseidon_push(data[j]);
        poseidon_push(data[j+1]);
        poseidon_push(data[j+2]);
        poseidon_push(data[j+3]);
        round ++;
        if (round==8) {
            r[0] = poseidon_finalize();
            r[1] = poseidon_finalize();
            r[2] = poseidon_finalize();
            r[3] = poseidon_finalize();
            round = 0;
            poseidon_new(0); // start another non-reset round
        }
    }
    // proceed with squeeze
    poseidon_push(1);
    poseidon_push(0);
    poseidon_push(0);
    poseidon_push(0);
    for (i=round+1; i<8; i++) {
        poseidon_push(0);
        poseidon_push(0);
        poseidon_push(0);
        poseidon_push(0);
    }
    r[0] = poseidon_finalize();
    r[1] = poseidon_finalize();
    r[2] = poseidon_finalize();
    r[3] = poseidon_finalize();
    wasm_dbg(r[0]);
    wasm_dbg(r[1]);
    wasm_dbg(r[2]);
    wasm_dbg(r[3]);
}
