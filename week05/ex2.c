#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_THREADS 100

struct Thread {
    int id;
    int i;
    char message[256];
};

void *thread_function(void *arg) {
    struct Thread *thread = (struct Thread *) arg;
    printf("Thread %d prints message: %s\n", thread->id, thread->message);
    pthread_exit(NULL);
}

int main() {
    int n;
    printf("Enter the number of threads to create (max %d): ", MAX_THREADS);
    scanf("%d", &n);
    if (n > MAX_THREADS) {
        printf("Error: Maximum number of threads exceeded.\n");
        return EXIT_FAILURE;
    }
    
    struct Thread threads[n];
    pthread_t tid[n];
    
    for (int i = 0; i < n; i++) {
        threads[i].id = i + 1;
        threads[i].i = i;
        sprintf(threads[i].message, "Hello from thread %d", i + 1);
        
        printf("Thread %d is created.\n", threads[i].id);
        
        pthread_create(&tid[i], NULL, thread_function, (void *) &threads[i]);
        pthread_join(tid[i], NULL);
    }
    
    return EXIT_SUCCESS;
}
