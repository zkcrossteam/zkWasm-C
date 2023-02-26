#include "zkwasmsdk.h"
#include "hash-wasm.h"
#include <stdint.h>
#include <stddef.h>
#include "rlp.h"

extern uint32_t select();
uint8_t buf[2048];
uint8_t *cursor;

__attribute__((visibility("default")))
uint32_t get_byte(uint32_t i) {
    return cursor[i];
}

struct rlpItemAllocator itemAllocator;

__attribute__((visibility("default")))
int zkmain() {
    uint32_t length = (uint32_t)wasm_input(1);
    read_bytes_from_u64(buf, length, 0);
    struct rlpItem *root = decode(buf, 0, &itemAllocator);
    struct rlpItem *anchor = root->firstChild;
    int sc = 0;
    while (anchor->next) {
       if(anchor->isString) {
           cursor = (uint8_t*)(buf + anchor->startPos);
           if(select()) {
               sc++;
           }
       }
       anchor = anchor->next;
    }
    return sc;
}
