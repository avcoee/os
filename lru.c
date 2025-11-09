#include <stdio.h>

void printFrames(int frames[], int capacity, int count) {
    for (int i = 0; i < capacity; i++) {
        if (i < count)
            printf("%d ", frames[i]);
        else
            printf("- ");
    }
    printf("\n");
}

int search(int frames[], int count, int page) {
    for (int i = 0; i < count; i++) {
        if (frames[i] == page)
            return i;
    }
    return -1;
}

void lru(int pages[], int n, int capacity) {
    int frames[capacity];
    int time[capacity];  // track last used time of pages in frames
    int count = 0, faults = 0, hits = 0, currentTime = 0;

    printf("\nRunning LRU with %d frames\n", capacity);

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int idx = search(frames, count, page);

        if (idx == -1) {
            // Page fault
            if (count < capacity) {
                frames[count] = page;
                time[count] = currentTime++;
                count++;
            } else {
                // Find least recently used page
                int lruIndex = 0;
                for (int j = 1; j < capacity; j++) {
                    if (time[j] < time[lruIndex]) {
                        lruIndex = j;
                    }
                }
                frames[lruIndex] = page;
                time[lruIndex] = currentTime++;
            }
            faults++;
        } else {
            // Page hit, update last used time
            time[idx] = currentTime++;
            hits++;
        }

        printf("After inserting page %d: ", page);
        printFrames(frames, capacity, count);
    }

    printf("\nTotal Page Faults = %d\n", faults);
    printf("Total Page Hits = %d\n", hits);
    printf("Fault Ratio = %.2f\n", (float)faults / n);
    printf("Hit Ratio = %.2f\n\n", (float)hits / n);
}

int main() {
    int n, pages[100];
    int capacity;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter the page reference string:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Running LRU for 3 frames:\n");
    lru(pages, n, 3);

    printf("Running LRU for 4 frames:\n");
    lru(pages, n, 4);

    return 0;
}
OUTPUT:avcoe@avcoe-Vostro-3710:~$ gcc lru.c
avcoe@avcoe-Vostro-3710:~$ ./a.out
Enter number of pages: 12
Enter the page reference string:
1
2
3
4
5
4
3
4
6
6
8
5
Running LRU for 3 frames:

Running LRU with 3 frames
After inserting page 1: 1 - - 
After inserting page 2: 1 2 - 
After inserting page 3: 1 2 3 
After inserting page 4: 4 2 3 
After inserting page 5: 4 5 3 
After inserting page 4: 4 5 3 
After inserting page 3: 4 5 3 
After inserting page 4: 4 5 3 
After inserting page 6: 4 6 3 
After inserting page 6: 4 6 3 
After inserting page 8: 4 6 8 
After inserting page 5: 5 6 8 

Total Page Faults = 8
Total Page Hits = 4
Fault Ratio = 0.67
Hit Ratio = 0.33

Running LRU for 4 frames:

Running LRU with 4 frames
After inserting page 1: 1 - - - 
After inserting page 2: 1 2 - - 
After inserting page 3: 1 2 3 - 
After inserting page 4: 1 2 3 4 
After inserting page 5: 5 2 3 4 
After inserting page 4: 5 2 3 4 
After inserting page 3: 5 2 3 4 
After inserting page 4: 5 2 3 4 
After inserting page 6: 5 6 3 4 
After inserting page 6: 5 6 3 4 
After inserting page 8: 8 6 3 4 
After inserting page 5: 8 6 5 4 

Total Page Faults = 8
Total Page Hits = 4
Fault Ratio = 0.67
Hit Ratio = 0.33



