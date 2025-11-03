#include <stdio.h>
#include "arc.h"

void simulateARC(int pages[], int n, int frames) 
{
    int T1[100], T2[100], B1[100], B2[100];
    int t1 = 0, t2 = 0, b1 = 0, b2 = 0;
    int p = 0, hits = 0, misses = 0;

    printf("\n=== ARC Page Replacement ===\n");

    for (int i = 0; i < n; i++) 
    {
        int page = pages[i];
        int hit = 0, found = 0;

        for (int j = 0; j < t1; j++) if (T1[j] == page) { found = 1; hit = 1; break; }
        for (int j = 0; j < t2; j++) if (T2[j] == page) { found = 1; hit = 1; break; }

        if (found) 
        {
            hits++;
        } else 
        {
            misses++;
            if (t1 + t2 >= frames) 
            {
                if (t1 > p) {
                    for (int j = 0; j < b1; j++) B1[j] = B1[j + 1];
                    B1[b1++] = T1[0];
                    for (int j = 0; j < t1 - 1; j++) T1[j] = T1[j + 1];
                    t1--;
                } else {
                    for (int j = 0; j < b2; j++) B2[j] = B2[j + 1];
                    B2[b2++] = T2[0];
                    for (int j = 0; j < t2 - 1; j++) T2[j] = T2[j + 1];
                    t2--;
                }
            }
            T1[t1++] = page;
        }

        printf("Request %2d -> [T1:", page);
        for (int j = 0; j < t1; j++) printf("%d ", T1[j]);
        printf("T2:");
        for (int j = 0; j < t2; j++) printf("%d ", T2[j]);
        printf("]  %s\n", hit ? " HIT" : "– MISS");
    }

    printf("Total Hits = %d | Misses = %d | Hit Ratio = %.2f\n",hits, misses, (float)hits / (hits + misses));
}
