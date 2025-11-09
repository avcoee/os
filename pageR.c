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
            return 1;
    }
    return 0;
}

void fifo(int pages[], int n, int capacity) {
    int frames[capacity];
    int count = 0, front = 0;
    int faults = 0, hits = 0;

    printf("\nRunning FIFO with %d frames\n", capacity);

    for (int i = 0; i < n; i++) {
        int page = pages[i];

        if (!search(frames, count, page)) {
            faults++;
            if (count < capacity) {
                frames[count++] = page;
            } else {
                frames[front] = page;
                front = (front + 1) % capacity;
            }
        } else {
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

    printf("Running FIFO for 3 frames:\n");
    fifo(pages, n, 3);

    printf("Running FIFO for 4 frames:\n");
    fifo(pages, n, 4);

    return 0;
}
OUTPUT:avcoe@avcoe-Vostro-3710:~$ gcc pageR.c
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
7
8
5
Running FIFO for 3 frames:

Running FIFO with 3 frames
After inserting page 1: 1 - - 
After inserting page 2: 1 2 - 
After inserting page 3: 1 2 3 
After inserting page 4: 4 2 3 
After inserting page 5: 4 5 3 
After inserting page 4: 4 5 3 
After inserting page 3: 4 5 3 
After inserting page 4: 4 5 3 
After inserting page 6: 4 5 6 
After inserting page 7: 7 5 6 
After inserting page 8: 7 8 6 
After inserting page 5: 7 8 5 

Total Page Faults = 9
Total Page Hits = 3
Fault Ratio = 0.75
Hit Ratio = 0.25

Running FIFO for 4 frames:

Running FIFO with 4 frames
After inserting page 1: 1 - - - 
After inserting page 2: 1 2 - - 
After inserting page 3: 1 2 3 - 
After inserting page 4: 1 2 3 4 
After inserting page 5: 5 2 3 4 
After inserting page 4: 5 2 3 4 
After inserting page 3: 5 2 3 4 
After inserting page 4: 5 2 3 4 
After inserting page 6: 5 6 3 4 
After inserting page 7: 5 6 7 4 
After inserting page 8: 5 6 7 8 
After inserting page 5: 5 6 7 8 

Total Page Faults = 8
Total Page Hits = 4
Fault Ratio = 0.67
Hit Ratio = 0.33



