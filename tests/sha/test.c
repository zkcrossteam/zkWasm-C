#include "zkwasmsdk.h"
#include "hash-wasm.h"
#include <stdint.h>
#include <stddef.h>
__attribute__((visibility("default")))
int zkmain() {
    uint8_t hash[32];
    uint8_t msg[1];
    msg[0] = (uint8_t)0;
    SHA256_Digest(hash, 1, msg);
    require(hash[0]==110);
    return 0;
}
