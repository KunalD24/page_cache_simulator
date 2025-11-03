#include <stdio.h>

void simulateLRU(int pages[], int n, int frames)
{
    int buffer[frames];
    int time[frames];
    int hits = 0, misses = 0, counter = 0;

    for (int i = 0; i < frames; i++)
    {
        buffer[i] = -1;
        time[i] = 0;
    }

    printf("\n--- LRU Simulation ---\n");

    for (int i = 0; i < n; i++)
    {
        int page = pages[i];
        int pos = -1;
        for (int j = 0; j < frames; j++)
        {
            if (buffer[j] == page)
            {
                pos = j;
                break;
            }
        }

        if (pos != -1)
        {
            hits++;
            time[pos] = ++counter;
        }
        else
        {
            misses++;
            int lru = 0;
            for (int j = 1; j < frames; j++)
                if (time[j] < time[lru])
                    lru = j;
            buffer[lru] = page;
            time[lru] = ++counter;
        }

        printf("Request %2d -> [", page);
        for (int j = 0; j < frames; j++)
            buffer[j] == -1 ? printf("_ ") : printf("%d ", buffer[j]);
        printf("]  (%s)\n", pos != -1 ? "HIT" : "MISS");
    }

    printf("Total Hits = %d | Misses = %d | Hit Ratio = %.2f\n",hits, misses, (float)hits / (hits + misses));
}
