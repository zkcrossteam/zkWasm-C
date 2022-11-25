#include <stdint.h>
#include "../include/rlp.h"

#include <stdint.h>

struct rlpItemAllocator itemAllocator;

__attribute__((visibility("default")))
int test_decode_string() {
    uint32_t length = (uint32_t)wasm_input(0);
    uint8_t buf[1024];
    read_bytes_from_u64(buf, length, true);
    struct rlpItem *root = decode(buf, 0, &itemAllocator);
    //decodeString(buf, 0, length, &itemAllocator);
    return root->len;
}
