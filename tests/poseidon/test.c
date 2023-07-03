#include "zkwasmsdk.h"
#include "hash-wasm.h"
#include <stdint.h>
#include <stddef.h>
__attribute__((visibility("default")))
int zkmain() {
    uint8_t hash[32];
    uint64_t msg[4];
    msg[0] = (uint64_t)0;
    msg[1] = (uint64_t)0;
    msg[2] = (uint64_t)0;
    msg[3] = (uint64_t)0;
    poseidon(msg, 1, (uint64_t*)hash);
    require(hash[0]==107);
    return 0;
}
