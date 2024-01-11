#include "cache.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct cache {
    char **array;
    int *ref_buf;
    int size;
    int head;
    int hand;
    int cmpm;
    int capm;
};

cache *cache_new(int size) {
    cache *c = malloc(sizeof(cache));
    c->size = size;
    c->head = 0;
    c->hand = 0;
    c->cmpm = 0;
    c->capm = 0;
    c->array = (char **) calloc(c->size, sizeof(char *));
    c->ref_buf = (int *) calloc(c->size, sizeof(int));
    return c;
}

int cache_full(cache *c) {
    if (c->head == c->size) {
        return 1;
    } else {
        return 0;
    }
}

int check_for(char *x, cache *c) {
    for (int i = 0; i < (c->head); i++) {
        if (strcmp(x, c->array[i]) == 0) {
            return i;
        }
    }
    return -1;
}

void insert(char *x, cache *m) {
    if (cache_full(m)) {
        fprintf(stderr, "master full\n");
    }
    m->array[m->head] = x;
    m->head += 1;
}

void fifo_check(char *x, cache *c, cache *m) {
    if (check_for(x, c) != -1) {
        printf("HIT\n");
        return;
    }
    printf("MISS\n");
    if (check_for(x, m) != -1) {
        c->capm += 1;
    } else {
        c->cmpm += 1;
        insert(x, m);
    }
    if (!cache_full(c)) {
        c->array[c->head] = x;
        c->head += 1;
        return;
    }
    for (int i = 0; i < (c->size) - 1; i++) {
        c->array[i] = c->array[i + 1];
    }
    c->array[c->size - 1] = x;
}

void lru_check(char *x, cache *c, cache *m) {
    int ind;
    if ((ind = check_for(x, c)) != -1) {
        printf("HIT\n");
        for (int i = ind; i < (c->head); i++) {
            c->array[i] = c->array[i + 1];
        }
        c->array[c->head - 1] = x;
        return;
    }
    printf("MISS\n");
    if (check_for(x, m) != -1) {
        c->capm += 1;
    } else {
        c->cmpm += 1;
        insert(x, m);
    }
    if (!cache_full(c)) {
        c->array[c->head] = x;
        c->head += 1;
        return;
    } else {
        for (int i = ind; i < (c->size) - 1; i++) {
            c->array[i] = c->array[i + 1];
        }
        c->array[c->size - 1] = x;
    }
}

void clock_check(char *x, cache *c, cache *m) {
    int i = check_for(x, c);
    if (i != -1) { //HIT
        c->ref_buf[i] = 1;
        printf("HIT\n");
    } else {
        printf("MISS\n");
        if (check_for(x, m) != -1) {
            c->capm += 1;
        } else {
            c->cmpm += 1;
            insert(x, m);
        }
        if (!cache_full(c)) {
            c->array[c->head] = x;
            c->head += 1;
            return;
        }
        while (c->ref_buf[c->hand] != 0) {
            c->ref_buf[c->hand] = 0;
            c->hand = (c->hand + 1) % c->size;
        }
        c->array[c->hand] = x;
        c->hand = (c->hand + 1) % c->size;
    }
}

void cache_delete(cache *c) {
    if (c != NULL) {
        if (c->array != NULL) {
            free(c->array);
        }
    }
    if (c->ref_buf != NULL) {
        free(c->ref_buf);
    }
    free(c);
}

void cache_print(cache *c) {
    printf("[");
    for (int i = 0; i < (c->size); i++) {
        if (c->array[i] == NULL) {
            printf(" _,");
        } else {
            printf(" %s,", c->array[i]);
        }
    }
    printf(" ]\n");
}

void print_misses(cache *c) {
    printf("%d %d\n", c->cmpm, c->capm);
}
