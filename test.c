#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>

#include "pkt_queue_lck.h"
#define CONSUMER 1
#define PRODUCER 4 
#define TEST_NUM 10000000

struct queue_root *queue;
volatile int total = TEST_NUM;
int complete;

void *producer_thread(void *para)
{
    int c = TEST_NUM / PRODUCER;
    for (; c > 0; c--)
    {
        int *val = (int *)malloc(sizeof(int));
        *val = random();
        queue_add(queue, val);
        /*
         *printf("Adding value %d\n", *val);
         */
    }

    complete++;
    return NULL;
}

void *consumer_thread(void *para)
{
     while (total) {
        int *val;
        val = (int *) queue_get(queue);
        if (val != NULL) {
            /*
             *printf("Getting value %d, %d left\n", *val, queue->size);
             */
            __sync_fetch_and_sub(&total, 1);
        }
     }

    return NULL;
}

int main()
{
    int p, c;
    complete = 0;
    pthread_attr_t attr;
    pthread_t threads[200];
    struct timeval then, now;
    gettimeofday(&then, NULL);
    srandom((unsigned int)then.tv_usec);

    init_queue(&queue);
    /* Now create some threads */
    pthread_attr_init(&attr);

    for (p = 0; p < PRODUCER; p++) {
        pthread_create(&threads[p], &attr, producer_thread, NULL);
        pthread_join(threads[p], NULL);
    }
    for (c = 0; c < CONSUMER; c++) {
        pthread_create(&threads[p + c], &attr, consumer_thread, NULL);
        pthread_join(threads[p + c], NULL);
    }

    gettimeofday(&now, NULL);

    printf("Executions in %.3g seconds\n", now.tv_sec - then.tv_sec + 1e-6 * (now.tv_usec - then.tv_usec));

    return 0;
}
