#include "zkwasmsdk.h"
#include "kvpair.h"
#include "hash-wasm.h"

void wasm_dbg(uint64_t);


struct merkle_store default_data_store(void) {
    struct merkle_store store = {
        {11826054925775482837ULL, 5943555147602679911ULL, 3550282808714298530ULL, 3363170373529648096ULL}
    };
    return store;
}

uint32_t merkle_get_data(struct merkle_store *store, const uint32_t key, uint64_t *data) {
    uint64_t datahash[4];
    uint64_t datahash_check[4];

    merkle_address(key);
    merkle_setroot(store->root[0]);
    merkle_setroot(store->root[1]);
    merkle_setroot(store->root[2]);
    merkle_setroot(store->root[3]);

    for (int i=0; i<DATA64_SIZE; i++) {
        datahash[i] = merkle_get();
    }
    uint32_t len = merkle_fetch_data();

    for (int j=0; j<len; j++) {
        data[j] = merkle_fetch_data();
    }

    poseidon(data, len, datahash_check);
    require(datahash[0] == datahash_check[0]);
    require(datahash[1] == datahash_check[1]);
    require(datahash[2] == datahash_check[2]);
    require(datahash[3] == datahash_check[3]);

    //enforce root does not change
    merkle_getroot();
    merkle_getroot();
    merkle_getroot();
    merkle_getroot();

    return len;
}

void merkle_set_data(struct merkle_store *store, const uint32_t key, uint64_t *data, uint32_t len) {
    merkle_address(key);
    merkle_setroot(store->root[0]);
    merkle_setroot(store->root[1]);
    merkle_setroot(store->root[2]);
    merkle_setroot(store->root[3]);
    uint64_t datahash[4];
    merkle_get();
    merkle_get();
    merkle_get();
    merkle_get();

    //enforce root does not change
    merkle_getroot();
    merkle_getroot();
    merkle_getroot();
    merkle_getroot();

    poseidon(data, len, datahash);

    for (int j=0; j<len; j++) {
        merkle_put_data(data[j]);
    }

    merkle_set(datahash[0]);
    merkle_set(datahash[1]);
    merkle_set(datahash[2]);
    merkle_set(datahash[3]);

    store->root[0] = merkle_getroot();
    store->root[1] = merkle_getroot();
    store->root[2] = merkle_getroot();
    store->root[3] = merkle_getroot();
}
