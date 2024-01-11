#pragma once

#include <stdio.h>

typedef struct cache cache;

cache *cache_new(int size);

int cache_full(cache *c);

int check_for(char *x, cache *c);

void insert(char *x, cache *m);

void fifo_check(char *x, cache *c, cache *m);

void lru_check(char *x, cache *c, cache *m);

void clock_check(char *x, cache *c, cache *m);

void cache_delete(cache *c);

void cache_print(cache *c);

void print_misses(cache *c);
