#include <stdint.h>

void merkle_setroot(uint64_t x);
void merkle_address(uint64_t x);
void merkle_set(uint64_t x);
void merkle_put_data(uint64_t x);
uint64_t merkle_get(void);
uint64_t merkle_fetch_data(void);
uint64_t merkle_getroot(void);


struct merkle_store {
    uint64_t root[4];
};

uint32_t merkle_get_data(struct merkle_store *store, const uint32_t key, uint64_t *data);
void merkle_set_data(struct merkle_store *store, const uint32_t key, uint64_t *data, uint32_t len);

struct merkle_store default_data_store(void);

#define DATA64_SIZE 4
#define DATA8_SIZE (DATA64_SIZE * 8)
