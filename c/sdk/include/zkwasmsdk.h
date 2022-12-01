#ifdef _MSC_VER
#define WASM_EXPORT
#define __inline__
#else
#define WASM_EXPORT __attribute__((visibility("default")))
#endif

#ifndef ZKWASM_SDK
#define ZKWASM_SDK
#include <stdint.h>

#ifndef NULL
#define NULL 0
#endif

#if defined(__wasm__)
uint64_t wasm_input(uint32_t);

static inline uint64_t wasm_public_input()
{
  return wasm_input(1);
}

static inline uint64_t wasm_private_input()
{
  return wasm_input(0);
}

void assert(int cond);
extern void require(int cond);

// Sometimes LLVM emits these functions during the optimization step
// even with -nostdlib -fno-builtin flags
void *memcpy(void *dst, const void *src, uint32_t cnt);
#endif

/* Convert list of u64 into bytes */
static __inline__ void read_bytes_from_u64(void *dst, int byte_length)
{
    uint64_t *dst64 = (uint64_t *)dst;
    for (int i = 0; i * 8 < byte_length; i++)
    {
        if (i * 8 + 8 < byte_length)
        {
            dst64[i] = wasm_public_input();
        }
        else
        {
            // less then 16 bytes on demand
            uint64_t uint64_cache = wasm_public_input();
            uint8_t *u8_p = (uint8_t *)&uint64_cache;
            for (int j = i * 8; j < byte_length; j++)
            {
                ((uint8_t *)dst)[j] = u8_p[j - i * 8];
            }
        }
    }
}
#endif
