#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <assert.h>

#include "include/rlp.h"


unsigned char *hexSteamToBytes(char *stream) {
    unsigned l = strlen(stream);
    unsigned char *byteStr = malloc(l/2);
    char b[3] = {0};
    for(int i = 0, j = 0; i < l; i += 2) {
        memcpy(b, &stream[i], 2);
        byteStr[j++] = strtol(b, NULL, 16);
    }
    return byteStr;
}

struct rlpItemAllocator itemAllocator;


void prettyPrint(int depth, unsigned char *stream, struct rlpItem *curr) {
    for(int i = 0; i <= depth; i++) {
        printf("  ");
    }
    if(curr->isString) {
        printf("string:[");
        for(int i = 0; i < curr->len; i++) {
            printf("%u,", stream[curr->startPos + i]);
        }
        printf("]\n");
    } else {
        printf("[ list(%d)\n", curr->len);
        struct rlpItem *cursor = curr->firstChild;
        for(int i = 0; i < curr->len && cursor; i++) {
            prettyPrint(depth + 1, stream, cursor);
            cursor = cursor->next;
        }

        for(int i = 0; i <= depth; i++) {
            printf("  ");
        }
        printf("]\n");
    }
}

int main() {
    uint8_t buf[128];
    char* test_data_path = "./test_data.txt";
    char line[4096] = {0};
    unsigned int line_count = 0;
    FILE *file = fopen(test_data_path, "r");
    assert(file);
    int count = 1;
    while (fgets(line, 4096, file)) {
        int len = strlen(line);
        unsigned char *bytes = hexSteamToBytes(&line[2]);
        printf("Line # %d\n", count++);
        struct rlpItem *root = decode(bytes, 0, &itemAllocator);
        prettyPrint(1, bytes, root);
        printf("**********************************\n");
    }
    fclose(file);
    return 0;
}
