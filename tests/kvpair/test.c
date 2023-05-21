#include "zkwasmsdk.h"
#include <stdint.h>
#include <stddef.h>
#include "kvpair.h"

__attribute__((visibility("default")))
int zkmain() {
    uint8_t root[32] = {166, 157, 178, 62, 35, 83, 140, 56, 9, 235, 134, 184, 20, 145, 63, 43, 245, 186, 75, 233, 43, 42, 187, 217, 104, 152, 219, 89, 125, 199, 161, 9};
    uint64_t address = 1;
    uint64_t buf[8];
    buf[0] = 1;
    kv_setroot((uint64_t*)root);
    kv_set(address, buf);
    kv_get(address, buf);
    require(buf[0] == 1);
    require(buf[1] == 0);
    kv_getroot((uint64_t*)root);
    log(root[0]);
    return 0;
}
