#include <stdio.h>

int find(int arr[], int size, int page)
{
    for (int i = 0; i < size; i++)
        if (arr[i] == page)
            return i;
    return -1;
}

void removeAt(int arr[], int *size, int index)
{
    for (int i = index; i < (*size) - 1; i++)
        arr[i] = arr[i + 1];
    (*size)--;
}

void addRight(int arr[], int *size, int page)
{
    arr[*size] = page;
    (*size)++;
}

int removeLeft(int arr[], int *size)
{
    if (*size == 0)
        return -1;
    int val = arr[0];
    for (int i = 0; i < (*size) - 1; i++)
        arr[i] = arr[i + 1];
    (*size)--;
    return val;
}

void printList(const char *name, int arr[], int size)
{
    printf("%s:[", name);
    for (int i = 0; i < size; i++)
    {
        printf("%d", arr[i]);
        if (i < size - 1)
            printf(",");
    }
    printf("] ");
}

void simulateARC(int pages[], int n, int frames)
{
    int T1[100], T2[100], B1[100], B2[100];
    int t1Size = 0, t2Size = 0, b1Size = 0, b2Size = 0;
    int p = 0, hits = 0, misses = 0;

    printf("\n--- ARC Simulation ---\n");

    for (int i = 0; i < n; i++)
    {
        int page = pages[i];
        const char *status = "MISS";
        int idx;

        if ((idx = find(T1, t1Size, page)) != -1 || (idx = find(T2, t2Size, page)) != -1)
        {
            hits++;
            status = "HIT";

            if ((idx = find(T1, t1Size, page)) != -1)
                removeAt(T1, &t1Size, idx);
            else
                removeAt(T2, &t2Size, idx);
            addRight(T2, &t2Size, page);
        }
        else if ((idx = find(B1, b1Size, page)) != -1)
        {
            misses++;
            status = "B1→T2";
            p = (p + ((b2Size > 0) ? b2Size / b1Size : 1));
            if (p > frames)
                p = frames;
            if (t1Size > p)
            {
                int old = removeLeft(T1, &t1Size);
                addRight(B1, &b1Size, old);
            }
            else
            {
                int old = removeLeft(T2, &t2Size);
                addRight(B2, &b2Size, old);
            }
            removeAt(B1, &b1Size, find(B1, b1Size, page));
            addRight(T2, &t2Size, page);
        }
        else if ((idx = find(B2, b2Size, page)) != -1)
        {
            misses++;
            status = "B2→T2";
            p = (p - ((b1Size > 0) ? b1Size / b2Size : 1));
            if (p < 0)
                p = 0;
            if (t1Size > p)
            {
                int old = removeLeft(T1, &t1Size);
                addRight(B1, &b1Size, old);
            }
            else
            {
                int old = removeLeft(T2, &t2Size);
                addRight(B2, &b2Size, old);
            }
            removeAt(B2, &b2Size, find(B2, b2Size, page));
            addRight(T2, &t2Size, page);
        }
        else
        {
            misses++;
            status = "NEW";
            int total = t1Size + t2Size;
            if (total >= frames)
            {
                if (t1Size > p)
                {
                    int old = removeLeft(T1, &t1Size);
                    addRight(B1, &b1Size, old);
                }
                else
                {
                    int old = removeLeft(T2, &t2Size);
                    addRight(B2, &b2Size, old);
                }
            }
            addRight(T1, &t1Size, page);
        }

        printf("Req %2d -> %-6s | ", page, status);
        printList("T1", T1, t1Size);
        printList("T2", T2, t2Size);
        printList("B1", B1, b1Size);
        printList("B2", B2, b2Size);
        printf("p=%d\n", p);
    }

    printf("Total Hits=%d | Misses=%d | Hit Ratio=%.2f\n", hits, misses, (float)hits / (hits + misses));
}
