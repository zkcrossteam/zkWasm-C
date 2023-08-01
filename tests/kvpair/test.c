#include "zkwasmsdk.h"
#include <stdint.h>
#include <stddef.h>
#include "kvpair.h"
void wasm_dbg(uint64_t);

__attribute__((visibility("default")))
int zkmain() {
    uint64_t address = 1;
    uint64_t buf[8];
    buf[0] = 3;
    struct merkle_store store = default_data_store();
    merkle_set_data(&store, address, buf, 1);
    buf[0] = 0;
    uint32_t len = merkle_get_data(&store, address, buf);
    require(len == 1);
    require(buf[0] == 3);
    require(buf[1] == 0);
    return 0;
}
