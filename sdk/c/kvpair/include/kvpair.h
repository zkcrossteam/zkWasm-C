#include <stdint.h>

void kvpair_address(uint64_t x);
void kvpair_set(uint64_t x);
uint64_t kvpair_get(void);

#define DATA64_SIZE 4 
#define DATA8_SIZE (DATA64_SIZE * 4)



static __inline__ void kv_get(uint64_t *treeid, const uint32_t key, uint64_t *data)
{
  kvpair_address(treeid[0]);
  kvpair_address(treeid[1]);
  kvpair_address(key);
  for (int i=0; i<DATA64_SIZE; i++) {
    data[i] = kvpair_get();
  }
}

static __inline__ void kv_set(uint64_t *treeid, const uint32_t key, uint64_t *data)
{
  kvpair_address(treeid[0]);
  kvpair_address(treeid[1]);
  kvpair_address(key);
  for (int i=0; i<DATA64_SIZE; i++) {
    kvpair_set(data[i]);
  }
}
