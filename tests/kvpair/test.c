#include "zkwasmsdk.h"
#include <stdint.h>
#include <stddef.h>
#include "kvpair.h"

__attribute__((visibility("default")))
int zkmain() {
    uint64_t address[3];
    address[2] = 1;
    uint64_t buf[8];
    buf[0] = 1;
    kv_set(address, address[2], buf); 
    kv_get(address, address[2], buf); 
    require(buf[0] == 1);
    return 0;
}
