#include "zkwasmsdk.h"
#include "hash-wasm.h"
#include <stdint.h>
#include <stddef.h>
__attribute__((visibility("default")))
int zkmain() {
    uint8_t hash[32];
    uint8_t msg[1];
    msg[0] = (uint8_t)0;
    sha256(msg, 1, (uint64_t*)hash);
    require(hash[0]==110);
    return 0;
}
