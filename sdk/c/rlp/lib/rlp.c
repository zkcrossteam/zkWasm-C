#include "rlp.h"

struct rlpItem* allocRlpItem(struct rlpItemAllocator *itemAllocator) {
    return &itemAllocator->items[itemAllocator->pos];
}


struct rlpItem *decodeString(uint8_t *stream, int start, int end, struct rlpItemAllocator *itemAllocator) {
    struct rlpItem *curr = allocRlpItem(itemAllocator);
    curr->isString = true;
    curr->firstChild = NULL;
    curr->next = NULL;
    if(start > end) {
        // empty string
        curr->len = 0;
        curr->startPos = -1;
    } else {
        curr->len = end - start + 1;
        curr->startPos = start;
    }
    itemAllocator->pos++;
    return curr;
}

struct rlpItem *decodeList(uint8_t *stream, int start, int end, struct rlpItemAllocator *itemAllocator, int *listLength) {
    // empty list
    if(start > end) return NULL;

    struct rlpItem *rlpFirstChild = allocRlpItem(itemAllocator);
    int index = start;
    int listSize = 0;
    struct rlpItem *cursor = rlpFirstChild;
    while(index <= end) {
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
    assert(index == end + 1);
    return rlpFirstChild;
}

struct rlpItem *decode(uint8_t *stream, int start, struct rlpItemAllocator *itemAllocator) {
    int lengthBytes, dataLength;
    int8_t type = decodeType(stream, start, &lengthBytes, &dataLength);

    if(type == SINGLE_CHAR) {
        return decodeString(stream, start, start, itemAllocator);
    } else if(type == SHORT_STRING) {
        return decodeString(stream, start + 1, start + dataLength, itemAllocator);
    } else if(type == LONG_STRING) {
        return decodeString(stream, start + 1 + lengthBytes, start + lengthBytes + dataLength, itemAllocator);
    } else if(type == SHORT_LIST) {
        struct rlpItem *curr = allocRlpItem(itemAllocator);
        curr->isString = false;
        itemAllocator->pos++;
        curr->firstChild = decodeList(stream, start + 1, start + dataLength, itemAllocator, &curr->len);
        curr->startPos = -1;
        curr->next = NULL;
        return curr;
    } else if(type == LONG_LIST) {
        struct rlpItem *curr = allocRlpItem(itemAllocator);
        curr->isString = false;
        itemAllocator->pos++;
        curr->firstChild = decodeList(stream, start + lengthBytes + 1, start + lengthBytes + dataLength, itemAllocator, &curr->len);
        curr->startPos = -1;
        curr->next = NULL;
        return curr;
    } else {
        return NULL;
    }
}


