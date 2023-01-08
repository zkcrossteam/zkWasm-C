#include "zkwasmsdk.h"

void assert(int cond)
{
    if (!cond) __builtin_unreachable();
}

#if defined(__wasm__)
void *memcpy(void *dst, const void *src, uint32_t cnt)
{
  uint8_t *destination = dst;
  const uint8_t *source = src;
  while (cnt)
  {
    *(destination++) = *(source++);
    --cnt;
  }
  return dst;
}
#endif
