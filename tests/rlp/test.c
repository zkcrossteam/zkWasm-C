#include "zkwasmsdk.h"
#include "hash-wasm.h"
#include <stdint.h>
#include <stddef.h>
#include "rlp.h"

struct rlpItemAllocator itemAllocator;

__attribute__((visibility("default")))
int zkmain() {
    uint32_t length = (uint32_t)wasm_input(1);
    uint8_t buf[1024];
    read_bytes_from_u64(buf, length, 0);
    struct rlpItem *root = decode(buf, 0, &itemAllocator);
    return root->len;
}
