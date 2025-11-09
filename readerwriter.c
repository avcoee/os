#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t x, wsem;  
pthread_t tid;
int readcount;

void initialize() {
    pthread_mutex_init(&x, NULL);
    pthread_mutex_init(&wsem, NULL);
    readcount = 0;
}

void *reader(void *param) {
    int waittime;
    waittime = rand() % 5;

    printf("\nReader is trying to enter");

    pthread_mutex_lock(&x);
    readcount++;
    if (readcount == 1) {
        pthread_mutex_lock(&wsem);   
    }
    pthread_mutex_unlock(&x);

    printf("\n%d reader(s) are inside", readcount);
    sleep(waittime);

    pthread_mutex_lock(&x);
    readcount--;
    if (readcount == 0) {
        pthread_mutex_unlock(&wsem); 
    }
    pthread_mutex_unlock(&x);

    printf("\nReader is leaving");
    pthread_exit(0);
}

void *writer(void *param) {
    int waittime;
    waittime = rand() % 3;

    printf("\nWriter is trying to enter");

    pthread_mutex_lock(&wsem);
    printf("\nWriter has entered");
    sleep(waittime);
    pthread_mutex_unlock(&wsem);

    printf("\nWriter is leaving");
    pthread_exit(0);
}

int main() {
    int n1, n2, i;
    initialize();

    printf("\nEnter the number of readers: ");
    scanf("%d", &n1);
    printf("\nEnter the number of writers: ");
    scanf("%d", &n2);

    for (i = 0; i < n1; i++) {
        pthread_create(&tid, NULL, reader, NULL);
    }
    for (i = 0; i < n2; i++) {
        pthread_create(&tid, NULL, writer, NULL);
    }

    sleep(30); 
    printf("\nExiting...\n");
    exit(0);
}

OUTPUT:
	avcoe@avcoe-Vostro-3710:~$ gedit readerwriter.c
	avcoe@avcoe-Vostro-3710:~$ g++  readerwriter.c
	avcoe@avcoe-Vostro-3710:~$ ./a.out

	Enter the number of readers: 3

	Enter the number of writers: 3

	Reader is trying to enter
	1 reader(s) are inside
	Reader is trying to enter
	2 reader(s) are inside
	Reader is trying to enter
	3 reader(s) are inside
	Writer is trying to enter
	Writer is trying to enter
	Writer is trying to enter
	Reader is leaving
	Reader is leaving
	Reader is leaving
	Writer has entered
	Writer is leaving
	Writer has entered
	Writer is leaving
	Writer has entered
	Writer is leaving
	Exiting...

