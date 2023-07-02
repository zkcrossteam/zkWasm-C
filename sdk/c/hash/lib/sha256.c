#include "hash-wasm.h"
#include "zkwasmsdk.h"

#define sha256_block_size 64
#define sha256_hash_size 32

void sha256(uint8_t* data, uint32_t size, uint64_t* r)
{
    int i;
    sha256_new(size);
    for(i=0; i<size; i=i+8) {
        uint64_t* a = (uint64_t *)(&data[i*8]);
        sha256_push(*a);
    }
    int offset = i;
    uint8_t buf[8] = {0};
    for(;i<size;i++) {
        buf[i-offset] = data[i];
    }
    sha256_push(*((uint64_t *)buf));
    r[0] = sha256_finalize();
    r[1] = sha256_finalize();
    r[2] = sha256_finalize();
    r[3] = sha256_finalize();
    wasm_dbg(r[0]);
    wasm_dbg(r[1]);
    wasm_dbg(r[2]);
    wasm_dbg(r[3]);
}
