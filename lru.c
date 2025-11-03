#include <stdio.h>
#include "lru.h"

void simulateLRU(int pages[], int n, int frames) {
    int buffer[frames], time[frames];
    int hits = 0, misses = 0, counter = 0;

    for (int i = 0; i < frames; i++) {
        buffer[i] = -1;
        time[i] = 0;
    }

    printf("\n=== LRU Page Replacement ===\n");
    for (int i = 0; i < n; i++) {
        int page = pages[i], hit = 0;
        int pos = -1;

        for (int j = 0; j < frames; j++)
            if (buffer[j] == page) { pos = j; break; }

        if (pos != -1) {
            hits++;
            time[pos] = ++counter;
            hit = 1;
        } else {
            misses++;
            int empty = -1;
            for (int j = 0; j < frames; j++)
                if (buffer[j] == -1) { empty = j; break; }

            if (empty != -1) {
                buffer[empty] = page;
                time[empty] = ++counter;
            } else {
                int lru = 0;
                for (int j = 1; j < frames; j++)
                    if (time[j] < time[lru])
                        lru = j;
                buffer[lru] = page;
                time[lru] = ++counter;
            }
        }

        printf("Request %2d -> [", page);
        for (int j = 0; j < frames; j++)
            buffer[j] != -1 ? printf("%d ", buffer[j]) : printf("_ ");
        printf("]  %s\n", hit ? "HIT" : "– MISS");
    }

    printf("Total Hits = %d | Misses = %d | Hit Ratio = %.2f\n",hits, misses, (float)hits / (hits + misses));
}
