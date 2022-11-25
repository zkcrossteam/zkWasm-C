#if defined(__wasm__)
#define NULL 0;
void assert(int cond)
{
    if (!cond) __builtin_unreachable();
}
#endif

unsigned long long wasm_input(int);

/* Convert list of u64 into bytes */
static __inline__ void read_bytes_from_u64(void *dst, int byte_length, bool is_public) {
    uint64_t *dst64 = (uint64_t*) dst;
    for (int i = 0; i * 8 < byte_length; i++) {
        if (i*8 + 8 < byte_length) {
            dst64[i] = wasm_input(is_public);
        } else {
            //less then 16 bytes on demand
            uint64_t uint64_cache = wasm_input(is_public);
            uint8_t *u8_p = (uint8_t *)uint64_cache;
            for (int j = i*8; j<byte_length; j++) {
              ((uint8_t *)dst)[j] = u8_p[j-i*8];
            }
        }
    }
}
