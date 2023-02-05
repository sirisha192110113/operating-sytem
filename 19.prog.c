#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#ifndef NUM_THREADS
#define NUM_THREADS 4
#endif

int shared = 0;

void *func3(void* param)
{
    printf("Incrementing the shared variable...\n");
    for (int i = 0; i < 10000; ++i) {
        shared += 1;
    }
    return 0;
}

int main()
{
    pthread_t threads[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_create(&threads[i], NULL, func3, NULL);
    }

    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    printf("%d\n", shared);
    exit(EXIT_SUCCESS);
}
Output:

Incrementing the shared variable...
Incrementing the shared variable...
Incrementing the shared variable...
Incrementing the shared variable...
30384
In this case, we will utilize the POSIX threads library and its built-in pthread_mutex_t type. pthread_mutex_t type variable is usually declared as static storage duration. Mutex should be initialized only once before it’s used. When the mutex is declared as static, one should use the PTHREAD_MUTEX_INITIALIZER macro to initialize it. Once the mutex is initialized, threads can use pthread_mutex_lock and pthread_mutex_unlock functions correspondingly. pthread_mutex_lock locks the mutex object passed as the only argument. If the mutex was already locked, the calling thread gets blocked until the mutex becomes available. pthread_mutex_unlock should be called to unlock the mutex. If there are threads waiting on the same mutex, the scheduling policy determines which one gets the object lock. Finally, we call pthread_join on each of the four threads and print the integer - shared, which in this case should have the correct value stored.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#ifndef NUM_THREADS
#define NUM_THREADS 4
#endif

int shared = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *func3(void* param)
{
    pthread_mutex_lock(&mutex);
    printf("Incrementing the shared variable...\n");
    for (int i = 0; i < 10000; ++i) {
        shared += 1;
    }
    pthread_mutex_unlock(&mutex);
    return 0;
}

int main()
{
    pthread_t threads[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_create(&threads[i], NULL, func3, NULL);
    }

    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    printf("%d\n", shared);
    exit(EXIT_SUCCESS);
}
