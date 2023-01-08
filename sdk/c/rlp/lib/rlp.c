#include "rlp.h"

struct rlpItem *decodeString(uint8_t *stream, int start, int length, struct rlpItemAllocator *itemAllocator) {
    struct rlpItem *curr = allocRlpItem(itemAllocator);
    curr->isString = true;
    curr->firstChild = NULL;
    curr->next = NULL;
    curr->len = length;
    curr->startPos = start;
    return curr;
}



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


