#ifndef __ZKWASM_RLP__
#define __ZKWASM_RLP__

#define SINGLE_CHAR 1
#define SHORT_STRING 2
#define LONG_STRING 3
#define SHORT_LIST 4
#define LONG_LIST 5
#define INVALID 0

#include <stdbool.h>
#include <zkwasmsdk.h>

uint8_t ruleType(uint8_t e);

struct rlpItem {
    uint8_t startPos;
    uint8_t isString;
    uint16_t padding;
    // theoretically rlp can support a single stirng up to 2^64
    int len;
    struct rlpItem *firstChild;
    struct rlpItem *next;
};

struct rlpItemAllocator {
    struct rlpItem items[128];
    uint8_t pos;
};


struct rlpItem* allocRlpItem(struct rlpItemAllocator *itemAllocator);

static inline int decodeLength(unsigned char *stream, int start, int length) {
    int sum = 0;
    for(int i = 0; i < length; i++) {
        sum *= 256;
        sum += stream[start + i];
    }
    return sum;
}

static inline uint8_t decodeType(uint8_t *stream, int start, int *lengthBytes, int* dataLength) {
    uint8_t ch = stream[start];
    if(ch >= 0x00 && ch <= 0x7f) {
        *lengthBytes = 0;
        *dataLength = 0;
        return SINGLE_CHAR;
    } else if(ch >= 0x80 && ch <= 0xb7) {
        *lengthBytes = 0;
        *dataLength = stream[start] - 0x80;
        return SHORT_STRING;
    }
    else if(ch >= 0xb8 && ch <= 0xbf) {
        *lengthBytes = stream[start] - 0xb7;
        *dataLength = decodeLength(stream, start + 1, *lengthBytes);
        return LONG_STRING;
    }
    else if(ch >= 0xc0 && ch <= 0xf7) {
        *lengthBytes = 0;
        *dataLength = stream[start] - 0xc0;
        return SHORT_LIST;
    }
    else if(ch >= 0xf8 && ch <= 0xff) {
        *lengthBytes = stream[start] - 0xf7;
        *dataLength = decodeLength(stream, start + 1, *lengthBytes);
        return LONG_LIST;
    }
    else return INVALID;
}

struct rlpItem *decode(unsigned char *stream, int start, struct rlpItemAllocator *itemAllocator);
#endif
