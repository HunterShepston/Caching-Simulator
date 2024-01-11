#include "cache.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Invalid arguments\n");
        return 1;
    }
    int opt = 0;
    int n = 3;
    char *policy = NULL;
    if ((opt = getopt(argc, argv, "N:")) != 1) {
        switch (opt) {
        case 'N':
            n = strtol(optarg, NULL, 10);
            if (!n) {
                fprintf(stderr, "Invalid cache size\n");
                return 1;
            }
            if (argc < 4) {
                fprintf(stderr, "Specify policy\n");
                return 1;
            }
            policy = argv[3];
            break;
        default: policy = argv[1]; break;
        }
    }
    char init[100];
    cache *c = cache_new(n);
    cache *master = cache_new(100);
    if (strcmp(policy, "-F") == 0) {
        while ((fgets(init, 100, stdin)) != NULL) {
            char *item = strdup(init);
            fifo_check(item, c, master);
            //cache_print(c);
        }
    } else if (strcmp(policy, "-L") == 0) {
        while (fgets(init, 100, stdin) != NULL) {
            char *item = strdup(init);
            lru_check(item, c, master);
        }
    } else if (strcmp(policy, "-C") == 0) {
        while (fgets(init, 100, stdin) != NULL) {
            char *item = strdup(init);
            clock_check(item, c, master);
        }
    } else {
        fprintf(stderr, "Invalid policy\n");
        return EXIT_FAILURE;
    }
    print_misses(c);
    //    cache_delete(c);
    //  cache_delete(master);
    return 0;
}
