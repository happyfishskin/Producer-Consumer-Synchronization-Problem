#include <stdio.h>
#include <unistd.h>  // For sleep()
#include <pthread.h>

#define BUFFER_SIZE 7

int buffer[BUFFER_SIZE];  // The buffer size is 7
int in = 0;  // Producer index
int out = 0;  // Consumer index

void *producer(void *param) {
    int nextProduced = 1;
    while (1) {
        while ((in + 1) % BUFFER_SIZE == out) {
            printf("Buffer is full, waiting...\n");
            sleep(1);  // Wait for space to be available
        }
        buffer[in] = nextProduced;
        in = (in + 1) % BUFFER_SIZE;
        printf("Produced: %d\n", nextProduced++);
    }
}

void *consumer(void *param) {
    int nextConsumed;
    while (1) {
        while (in == out) {
            printf("Buffer is empty, waiting...\n");
            sleep(1);  // Wait for items to be produced
        }
        nextConsumed = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        printf("Consumed: %d\n", nextConsumed);
    }
}

int main() {
    pthread_t producerThread, consumerThread;

    // Create threads for producer and consumer
    pthread_create(&producerThread, NULL, producer, NULL);
    pthread_create(&consumerThread, NULL, consumer, NULL);

    // Wait for threads to finish (in this case, they run forever)
    pthread_join(producerThread, NULL);
    pthread_join(consumerThread, NULL);

    return 0;
}
