#include <stdio.h>
#include "clock.h"

void simulateClock(int pages[], int n, int frames) {
    int buffer[frames], refBit[frames];
    int pointer = 0, hits = 0, misses = 0;

    for (int i = 0; i < frames; i++) {
        buffer[i] = -1;
        refBit[i] = 0;
    }

    printf("\n=== Clock Page Replacement ===\n");
    for (int i = 0; i < n; i++) {
        int page = pages[i], found = 0, hit = 0;

        for (int j = 0; j < frames; j++) {
            if (buffer[j] == page) {
                found = 1; hit = 1;
                refBit[j] = 1; hits++;
                break;
            }
        }

        if (!found) {
            misses++;
            while (1) {
                if (refBit[pointer] == 0) {
                    buffer[pointer] = page;
                    refBit[pointer] = 1;
                    pointer = (pointer + 1) % frames;
                    break;
                } else {
                    refBit[pointer] = 0;
                    pointer = (pointer + 1) % frames;
                }
            }
        }

        printf("Request %2d -> [", page);
        for (int j = 0; j < frames; j++)
            buffer[j] != -1 ? printf("%d ", buffer[j]) : printf("_ ");
        printf("]  %s\n", hit ? " HIT" : "– MISS");
    }

    printf("Total Hits = %d | Misses = %d | Hit Ratio = %.2f\n",hits, misses, (float)hits / (hits + misses));
}
