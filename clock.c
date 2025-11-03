#include <stdio.h>

void simulateClock(int pages[], int n, int frames)
{
    int buffer[frames];
    int refBit[frames];
    int pointer = 0, hits = 0, misses = 0;

    for (int i = 0; i < frames; i++)
    {
        buffer[i] = -1;
        refBit[i] = 0;
    }

    printf("\n--- Clock Simulation ---\n");

    for (int i = 0; i < n; i++)
    {
        int page = pages[i];
        int found = 0;

        for (int j = 0; j < frames; j++)
        {
            if (buffer[j] == page)
            {
                found = 1;
                refBit[j] = 1;
                hits++;
                break;
            }
        }

        if (!found)
        {
            misses++;
            while (1)
            {
                if (refBit[pointer] == 0)
                {
                    buffer[pointer] = page;
                    refBit[pointer] = 1;
                    pointer = (pointer + 1) % frames;
                    break;
                }
                else
                {
                    refBit[pointer] = 0;
                    pointer = (pointer + 1) % frames;
                }
            }
        }

        printf("Request %2d -> [", page);
        for (int j = 0; j < frames; j++)
            buffer[j] == -1 ? printf("_ ") : printf("%d ", buffer[j]);
        printf("]  (%s)\n", found ? "HIT" : "MISS");
    }

    printf("Total Hits = %d | Misses = %d | Hit Ratio = %.2f\n",hits, misses, (float)hits / (hits + misses));
}
