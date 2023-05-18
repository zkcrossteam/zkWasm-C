#include "zkwasmsdk.h"
#include <stdint.h>
#include <stddef.h>
#include "kvpair.h"

__attribute__((visibility("default")))
int zkmain() {
    uint64_t root[4];
    uint64_t address = 1;
    uint64_t buf[8];
    buf[0] = 1;
    kv_setroot(root);
    kv_set(address, buf);
    kv_get(address, buf);
    require(buf[0] == 1);
    return 0;
}
