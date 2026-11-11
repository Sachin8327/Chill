#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define NUM_PRODUCERS 2
#define NUM_CONSUMERS 2
#define NUM_ITEMS 10

int buffer[BUFFER_SIZE];
int in_index = 0;
int out_index = 0;
pthread_mutex_t mutex;
sem_t empty;
sem_t full;

void* producer(void* arg) {
    int id = *((int*)arg);
    for (int i = 0; i < NUM_ITEMS; i++) {
        int item = (id * 100) + i;
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        buffer[in_index] = item;
        printf("Producer %d: Inserted item %d at index %d\n", id, item, in_index);
        in_index = (in_index + 1) % BUFFER_SIZE;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
        sleep(1);
    }
    pthread_exit(NULL);
}

void* consumer(void* arg) {
    int id = *((int*)arg);
    for (int i = 0; i < NUM_ITEMS; i++) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        int item = buffer[out_index];
        printf("Consumer %d: Removed item %d from index %d\n", id, item, out_index);
        out_index = (out_index + 1) % BUFFER_SIZE;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        sleep(2);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t prod_threads[NUM_PRODUCERS];
    pthread_t cons_threads[NUM_CONSUMERS];
    int thread_ids[2] = {1, 2};
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_create(&prod_threads[i], NULL, producer, &thread_ids[i]);
    }
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_create(&cons_threads[i], NULL, consumer, &thread_ids[i]);
    }
    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_join(prod_threads[i], NULL);
    }
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_join(cons_threads[i], NULL);
    }
    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);
    printf("Main thread exiting.\n");
    return 0;
}



// A. Header Files
// 1. stdio.h – printf() ke liye.
// 2. stdlib.h – General utility functions.
// 3. pthread.h – Thread creation, joining aur mutex ke liye.
// 4. semaphore.h – Semaphore operations ke liye.
// 5. unistd.h – sleep() function ke liye.

// B. Macros
// 1. BUFFER_SIZE = 5 – Buffer mein maximum 5 items store honge.
// 2. NUM_PRODUCERS = 2 – Total 2 Producer threads.
// 3. NUM_CONSUMERS = 2 – Total 2 Consumer threads.
// 4. NUM_ITEMS = 10 – Har Producer aur Consumer 10 iterations execute karega.

// C. Global Variables
// 1. buffer[] – Shared circular buffer jo Producer aur Consumer dono access karte hain.
// 2. in_index – Next item insertion ka index.
// 3. out_index – Next item removal ka index.
// 4. mutex – Critical section mein mutual exclusion maintain karta hai.
// 5. empty – Buffer mein available empty slots count karta hai.
// 6. full – Buffer mein available filled slots count karta hai.

// D. Producer Function
// 1. int id = *((int*)arg) – Thread ko pass ki gayi ID extract karta hai.
// 2. for loop – Har Producer 10 items generate karta hai.
// 3. int item = (id * 100) + i – Unique-looking item generate karta hai.
// 4. sem_wait(&empty) – Empty slot available hone ka wait karta hai. Empty slots 0 hone par block hota hai.
// 5. pthread_mutex_lock(&mutex) – Critical section enter karne se pehle mutex lock karta hai.
// 6. buffer[in_index] = item – Buffer mein item insert karta hai.
// 7. printf() – Inserted item aur index display karta hai.
// 8. in_index = (in_index + 1) % BUFFER_SIZE – Circular buffer ka next insertion index calculate karta hai.
// 9. pthread_mutex_unlock(&mutex) – Critical section complete hone par mutex unlock karta hai.
// 10. sem_post(&full) – Full semaphore increment karta hai, kyunki ek item available ho gaya.
// 11. sleep(1) – Producer 1 second ke liye sleep karta hai.
// 12. pthread_exit(NULL) – Producer thread terminate karta hai.

// E. Consumer Function
// 1. int id = *((int*)arg) – Consumer thread ki ID extract karta hai.
// 2. for loop – Har Consumer 10 items consume karta hai.
// 3. sem_wait(&full) – Available item ka wait karta hai. Full semaphore 0 hone par block hota hai.
// 4. pthread_mutex_lock(&mutex) – Shared buffer access karne ke liye mutex lock karta hai.
// 5. int item = buffer[out_index] – Buffer se item read karta hai.
// 6. printf() – Removed item aur index display karta hai.
// 7. out_index = (out_index + 1) % BUFFER_SIZE – Circular buffer ka next removal index calculate karta hai.
// 8. pthread_mutex_unlock(&mutex) – Critical section se exit karke mutex unlock karta hai.
// 9. sem_post(&empty) – Empty semaphore increment karta hai, kyunki ek slot available ho gaya.
// 10. sleep(2) – Consumer 2 seconds ke liye sleep karta hai.
// 11. pthread_exit(NULL) – Consumer thread terminate karta hai.

// F. Main Function
// 1. pthread_t prod_threads[] – Producer thread handles store karta hai.
// 2. pthread_t cons_threads[] – Consumer thread handles store karta hai.
// 3. thread_ids[] = {1, 2} – Producer aur Consumer ko IDs provide karta hai.
// 4. pthread_mutex_init() – Mutex initialize karta hai.
// 5. sem_init(&empty, 0, BUFFER_SIZE) – Empty semaphore ko 5 se initialize karta hai.
// 6. sem_init(&full, 0, 0) – Full semaphore ko 0 se initialize karta hai.
// 7. First for loop – pthread_create() se 2 Producer threads create karta hai.
// 8. Second for loop – pthread_create() se 2 Consumer threads create karta hai.
// 9. First pthread_join() loop – Dono Producer threads ke complete hone ka wait karta hai.
// 10. Second pthread_join() loop – Dono Consumer threads ke complete hone ka wait karta hai.
// 11. pthread_mutex_destroy() – Mutex destroy karta hai.
// 12. sem_destroy() – Dono semaphores destroy karta hai.
// 13. printf() – Main thread exit message display karta hai.
// 14. return 0 – Program successfully terminate karta hai.