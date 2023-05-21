#include <stdint.h>

void kvpair_setroot(uint64_t x);
void kvpair_address(uint64_t x);
void kvpair_set(uint64_t x);
uint64_t kvpair_get(void);
uint64_t kvpair_getroot(void);

#define DATA64_SIZE 4
#define DATA8_SIZE (DATA64_SIZE * 8)

static __inline__ void kv_setroot(uint64_t *root)
{
  for (int i=0; i<DATA64_SIZE; i++) {
    kvpair_setroot(root[i]);
  }
}

static __inline__ void kv_getroot(uint64_t *data)
{
  for (int i=0; i<DATA64_SIZE; i++) {
    data[i] = kvpair_getroot();
  }
}

static __inline__ void kv_get(const uint32_t key, uint64_t *data)
{
  kvpair_address(key);
  for (int i=0; i<DATA64_SIZE; i++) {
    data[i] = kvpair_get();
  }
}

static __inline__ void kv_set(const uint32_t key, uint64_t *data)
{
  kvpair_address(key);
  for (int i=0; i<DATA64_SIZE; i++) {
    kvpair_set(data[i]);
  }
}
