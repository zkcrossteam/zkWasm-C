#include "zkwasmsdk.h"
#include "hash-wasm.h"
#include <stdint.h>
#include <stddef.h>
#include "rlp.h"

extern uint32_t compare();
uint32_t c[2];

__attribute__((visibility("default")))
uint32_t get_byte(uint32_t i) {
    return c[i];
}

__attribute__((visibility("default")))
int zkmain() {
    uint32_t a = wasm_input(1);
    uint32_t b = wasm_input(1);
    c[0] = a;
    c[1] = b;
    require(compare() == 0);
    return 0;
}
