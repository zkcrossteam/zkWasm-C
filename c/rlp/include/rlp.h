#ifndef __ZKWASM_RLP__

#define __ZKWASM_RLP__

#define SINGLE_CHAR 1
#define SHORT_STRING 2
#define LONG_STRING 3
#define SHORT_LIST 4
#define LONG_LIST 5
#define INVALID 0

#include <stdbool.h>
#include <sdk.h>

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


struct rlpItem* allocRlpItem(struct rlpItemAllocator *itemAllocator) {
    uint8_t pos = itemAllocator->pos;
    itemAllocator->pos++;
    return &itemAllocator->items[pos-1];
}

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


struct rlpItem *decodeString(uint8_t *stream, int start, int length, struct rlpItemAllocator *itemAllocator) {
    struct rlpItem *curr = allocRlpItem(itemAllocator);
    curr->isString = true;
    curr->firstChild = NULL;
    curr->next = NULL;
    curr->len = length;
    curr->startPos = start;
    return curr;
}


struct rlpItem *decode(unsigned char *stream, int start, struct rlpItemAllocator *itemAllocator);


struct rlpItem *decodeList(uint8_t *stream, int start, int length, struct rlpItemAllocator *itemAllocator, int *listLength) {
    if(length == 0) {
        return NULL;
    } else {
        struct rlpItem *rlpFirstChild = allocRlpItem(itemAllocator);
        int index = start;
        int end = index + length;
        int listSize = 0;
        struct rlpItem *cursor = rlpFirstChild;
        while(index < end) {
            int lengthBytes, dataLength;
            decodeType(stream, index, &lengthBytes, &dataLength);
            struct rlpItem *curr = decode(stream, index, itemAllocator);
            if(index != start) {
                cursor->next = curr;
                cursor = cursor->next;
            }
            index += 1 + lengthBytes + dataLength;
            listSize++;
        }
        *listLength = listSize;
        //check same level tranverse correction
        assert(index == end);
        return rlpFirstChild;
    }
}

struct rlpItem *decode(unsigned char *stream, int start, struct rlpItemAllocator *itemAllocator) {
    int lengthBytes, dataLength;
    int8_t type = decodeType(stream, start, &lengthBytes, &dataLength);

    //printf("decode[%u] start %u, lbytes %u, length %u\n", type, start, lengthBytes, dataLength);
    if(type == SINGLE_CHAR) {
        return decodeString(stream, start, 0, itemAllocator);
    } else if(type == SHORT_STRING) {
        return decodeString(stream, start + 1, dataLength, itemAllocator);
    } else if(type == LONG_STRING) {
        return decodeString(stream, start + 1 + lengthBytes, dataLength, itemAllocator);
    } else if(type == SHORT_LIST) {
        struct rlpItem *curr = allocRlpItem(itemAllocator);
        curr->isString = false;
        curr->firstChild = decodeList(stream, start + 1, dataLength, itemAllocator, &curr->len);
        curr->startPos = -1;
        curr->next = NULL;
        return curr;
    } else if(type == LONG_LIST) {
        struct rlpItem *curr = allocRlpItem(itemAllocator);
        curr->isString = false;
        curr->firstChild = decodeList(stream, start + lengthBytes + 1, dataLength, itemAllocator, &curr->len);
        curr->startPos = -1;
        curr->next = NULL;
        return curr;
    } else {
        return NULL;
    }
}

#endif
