#include "zkwasmsdk.h"
#include "hash-wasm.h"
#include <stdint.h>
#include <stddef.h>
#include "rlp.h"

extern uint32_t inc(uint32_t a);

__attribute__((visibility("default")))
int zkmain() {
    uint32_t a = wasm_input(1);
    require(inc(a) > 10);
    return 0;
}
