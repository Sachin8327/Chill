#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define N 5

sem_t ch[N];
sem_t room;

void *philosopher(void *arg)
{
    int i = *(int *)arg;
    int left, right;

    left = i;
    right = (i + 1) % N;

    printf("\n%d philosopher is created", i);
    printf("\n%d philosopher is hungry", i);

    sem_wait(&room);

    sem_wait(&ch[left]);
    sem_wait(&ch[right]);

    printf("\n%d philosopher is eating", i);

    sleep(2);

    sem_post(&ch[right]);
    sem_post(&ch[left]);

    printf("\n%d philosopher has completed eating", i);

    sem_post(&room);

    return NULL;
}

int main()
{
    int i;
    int id[N];
    pthread_t pid[N];

    for(i = 0; i < N; i++)
        sem_init(&ch[i], 0, 1);

    sem_init(&room, 0, 4);

    for(i = 0; i < N; i++)
    {
        id[i] = i;
        pthread_create(&pid[i], NULL, philosopher, &id[i]);
    }

    for(i = 0; i < N; i++)
        pthread_join(pid[i], NULL);

    for(i = 0; i < N; i++)
        sem_destroy(&ch[i]);

    sem_destroy(&room);

    return 0;
}



// Deadlock ke 4 Necessary Conditions
// Deadlock tab possible hota hai jab following four conditions simultaneously satisfy hoti hain:
// 1. Mutual Exclusion
//    - Ek resource ek time par sirf ek process ko allocate kiya ja sakta hai.
//    - Dining Philosopher mein ek chopstick ek time par ek philosopher use karta hai.
// 2. Hold and Wait
//    - Process ek resource hold karke doosre resource ka wait karta hai.
//    - Philosopher left chopstick hold karke right chopstick ka wait karta hai.
// 3. No Preemption
//    - Resource forcibly process se remove nahi kiya ja sakta.
//    - Philosopher se chopstick forcibly nahi li jaati; woh khud release karta hai.
// 4. Circular Wait
//    - Processes circular chain mein resources ka wait karte hain.
//    - P0, P1 ka wait; P1, P2 ka wait; ...; P4, P0 ka wait.

// 8. Starvation
// Definition
// Starvation ek situation hai jisme koi process indefinitely resource ka wait karta rehta hai, jabki other processes repeatedly resource obtain karte rehte hain.
// Dining Philosopher mein Starvation
// 1. Ek philosopher hungry ho jata hai.
// 2. Usko chopsticks available nahi milti.
// 3. Other philosophers repeatedly chopsticks acquire aur release karte hain.
// 4. Waiting philosopher ko repeatedly chance nahi milta.
// 5. Woh indefinitely hungry reh sakta hai.
// Important: Hamara code deadlock prevent karta hai, lekin starvation prevent karne ki guarantee nahi deta.

// Starvation prevent karne ke liye fair scheduling ya FIFO-based resource allocation use kiya ja sakta hai.
// 9. Critical Section
// 1. Critical section program ka woh part hota hai jo shared resource access karta hai.
// 2. Dining Philosopher mein chopstick acquire/release operations shared resources ke access ko control karte hain.
// 3. Semaphore ensure karta hai ki ek chopstick simultaneously multiple philosophers ko allocate na ho.
// 4. Isse resource conflict aur race conditions prevent hoti hain.

// 11. Limitations
// 1. Starvation-free execution guarantee nahi hota.
// 2. Semaphore scheduling fairness guaranteed nahi hai.
// 3. Maximum 4 philosophers ki restriction kuch situations mein concurrency limit karti hai.
// 4. Code mein philosopher sirf ek baar eat karta hai.
// 5. Thinking state explicitly implement nahi hai.


// 1. Header Files
// - stdio.h – Used for input/output operations like printf().
// - unistd.h – Used for the sleep() function.
// - pthread.h – Used to create and manage threads.
// - semaphore.h – Used for semaphore operations like sem_init(), sem_wait() and sem_post().
// 2. Constant Declaration
// - #define N 5 – Defines the total number of philosophers as 5.
// 3. Semaphore Declaration
// - sem_t ch[N] – An array of 5 semaphores representing 5 chopsticks.
// - Each chopstick semaphore is initialized to 1, meaning each chopstick is initially available.
// - sem_t room – Controls how many philosophers can try to pick up chopsticks simultaneously.
// 4. Philosopher Function
// Function: void *philosopher(void *arg)

// This function represents the activity performed by each philosopher thread.
// 1. int i = *(int *)arg;
//    - Retrieves the philosopher's ID passed to the thread.
// 2. left = i;
//    - Assigns the left chopstick to the philosopher's ID.
// 3. right = (i + 1) % N;
//    - Assigns the right chopstick.
//    - Modulo ensures that the last philosopher gets chopstick 0 as the right chopstick.
// 4. printf() statements:
//    - Display that the philosopher is created and hungry.
// 5. sem_wait(&room);
//    - Allows the philosopher to enter the room.
//    - At most 4 philosophers can enter simultaneously because the initial value of room is 4.
// 6. sem_wait(&ch[left]);
//    - Acquires the left chopstick.
//    - If unavailable, the philosopher waits.
// 7. sem_wait(&ch[right]);
//    - Acquires the right chopstick.
//    - If unavailable, the philosopher waits.
// 8. printf() – Displays that the philosopher is eating.
// 9. sleep(2);
//    - Simulates the time taken by the philosopher to eat.
//    - The thread pauses for 2 seconds.
// 10. sem_post(&ch[right]);
//     - Releases the right chopstick.
// 11. sem_post(&ch[left]);
//     - Releases the left chopstick.
// 12. printf() – Displays that the philosopher has completed eating.
// 13. sem_post(&room);
//     - Releases the room semaphore.
//     - Allows another waiting philosopher to enter.
// 14. return NULL;
//     - Terminates the philosopher thread.
// 5. Main Function
// Function: int main()
// 1. int i; – Loop counter.
// 2. int id[N]; – Stores the IDs of all five philosophers.
// 3. pthread_t pid[N]; – Stores the thread IDs of all five philosopher threads.
// Initialization of chopsticks:
// for(i = 0; i < N; i++)
//     sem_init(&ch[i], 0, 1);


// - Initializes all five chopstick semaphores.
// - 0 means the semaphore is shared between threads of the same process.
// - 1 means each chopstick is initially available.
// Initialization of room:
// sem_init(&room, 0, 4);


// - Initializes the room semaphore with value 4.
// - Allows a maximum of four philosophers to attempt to acquire chopsticks at a time.
// - This helps prevent deadlock.
// Creation of philosopher threads:
// for(i = 0; i < N; i++)
// {
//     id[i] = i;
//     pthread_create(&pid[i], NULL, philosopher, &id[i]);
// }


// - Creates five philosopher threads.
// - Each thread receives a unique philosopher ID.
// - Each thread executes the philosopher() function independently.
// Waiting for threads:
// for(i = 0; i < N; i++)
//     pthread_join(pid[i], NULL);


// - Makes the main thread wait until all five philosopher threads finish execution.
// - Prevents the main program from terminating prematurely.
// Destroying semaphores:
// for(i = 0; i < N; i++)
//     sem_destroy(&ch[i]);

// sem_destroy(&room);


// - Destroys all initialized semaphores after their use.
// - Releases associated semaphore resources.
// 6. Important Logic: How Deadlock Is Prevented
// - Normally, if all five philosophers pick up their left chopstick simultaneously, each waits for the right chopstick.
// - This creates a circular wait and results in deadlock.
// - In this program, room is initialized to 4.
// - Therefore, only four philosophers can attempt to acquire chopsticks simultaneously.
// - This breaks the circular-wait condition and prevents deadlock.
// 7. Important Functions for Viva
// Function	Purpose
// pthread_create()	Creates a new thread
// pthread_join()	Waits for a thread to finish
// sem_init()	Initializes a semaphore
// sem_wait()	Acquires/decrements a semaphore
// sem_post()	Releases/increments a semaphore
// sem_destroy()	Destroys a semaphore
// sleep(2)	Pauses execution for 2 seconds

// Remember: ch[] controls access to individual chopsticks, while room limits the number of philosophers trying to acquire chopsticks simultaneously.