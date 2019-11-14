#define _CRT_SECURE_NO_WARNINGS
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
 
#define SEED 1093
#define MODULATOR 9677
 
FILE * fin;
FILE* fout;
 
typedef struct list {
    int value;
    struct list* next;
} list_t;
 
typedef struct set {
    list_t** hashes;
} set_t;
 
set_t* create_set(int size) {
    set_t* s = (set_t*)malloc(sizeof(set_t));
    s->hashes = (list_t * *)calloc(size, sizeof(list_t*));
    return s;
}
 
uint32_t murmur3_32(const uint8_t* key, size_t len, uint32_t seed)
{
    uint32_t h = seed;
    if (len > 3) {
        size_t i = len >> 2;
        do {
            uint32_t k;
            memcpy(&k, key, sizeof(uint32_t));
            key += sizeof(uint32_t);
            k *= 0xcc9e2d51;
            k = (k << 15) | (k >> 17);
            k *= 0x1b873593;
            h ^= k;
            h = (h << 13) | (h >> 19);
            h = h * 5 + 0xe6546b64;
        } while (--i);
    }
    if (len & 3) {
        size_t i = len & 3;
        uint32_t k = 0;
        do {
            k <<= 8;
            k |= key[i - 1];
        } while (--i);
        k *= 0xcc9e2d51;
        k = (k << 15) | (k >> 17);
        k *= 0x1b873593;
        h ^= k;
    }
    h ^= len;
    h ^= h >> 16;
    h *= 0x85ebca6b;
    h ^= h >> 13;
    h *= 0xc2b2ae35;
    h ^= h >> 16;
    return h;
}
 
int hash_func(int x) {
    return murmur3_32((void*)& x, sizeof(x), SEED) % MODULATOR;
}
 
void insert(set_t* s, int x) {
    int h = hash_func(x);
    list_t* v = s->hashes[h];
 
    if (v == NULL) {
        v = (list_t*)malloc(sizeof(list_t));
        v->value = x;
        v->next = NULL;
        s->hashes[h] = v;
        return;
    }
 
    while (v->next != NULL) {
        if (v->value == x) return;
        v = v->next;
    }
 
    if (v->value == x) return;
 
    v->next = (list_t*)malloc(sizeof(list_t));
    v->next->value = x;
    v->next->next = NULL;
}
 
void delete(set_t* s, int x) {
    int h = hash_func(x);
    list_t* v = s->hashes[h];
    list_t* prev = v;
    int i = 0;
    while (v != NULL) {
        if (v->value == x && i == 0) {
            s->hashes[h] = v->next;
            free(v);
            return;
        }
        else if (v->value == x) {
            prev->next = v->next;
            free(v);
            return;
        }
        prev = v;
        v = v->next;
        i = 1;
    }
}
 
void exists(set_t* s, int x) {
    int h = hash_func(x);
    list_t* v = s->hashes[h];
    if (v != NULL) {
        do {
            if (v->value == x) {
                fprintf(fout, "true\n");
                return;
            }
            v = v->next;
        } while (v != NULL);
    }
    fprintf(fout, "false\n");
}
 
int main() {
    fin = fopen("set.in", "r");
    fout = fopen("set.out", "w");
    char buffer[20];
    int x;
    set_t* hash = create_set(MODULATOR);
    while (fscanf(fin, "%s", buffer) != EOF) {
        switch (buffer[0])
        {
        case 'i':
            fscanf(fin, "%d", &x);
            insert(hash, x);
            break;
        case 'e':
            fscanf(fin, "%d", &x);
            exists(hash, x);
            break;
        case 'd':
            fscanf(fin, "%d", &x);
            delete(hash, x);
            break;
        }
    }
}
