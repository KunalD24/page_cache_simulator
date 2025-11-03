#include <stdio.h>
#include "lru.h"
#include "clock.h"
#include "arc.h"

int main()
{
    int choice;
    int pages[] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
    int n = sizeof(pages) / sizeof(pages[0]);
    int frames = 3;

    while (1)
    {
        printf("\n=== PAGE CACHE SIMULATOR ===\n");
        printf("Select Replacement Policy:\n");
        printf("1. LRU\n");
        printf("2. Clock\n");
        printf("3. ARC\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            simulateLRU(pages, n, frames);
            break;

        case 2:
            simulateClock(pages, n, frames);
            break;

        case 3:
            simulateARC(pages, n, frames);
            break;

        case 4:
            printf("Exiting simulator. Goodbye!\n");
            return 0;

        default:
            printf("Invalid choice! Please select 1–4.\n");
        }
    }

    return 0;
}
