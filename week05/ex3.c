# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
#include <pthread.h>
// primality test

int total = 0;
bool is_prime(int n){
    if (n <= 1) return false ;
    int i = 2;
    for (; i * i <= n; i++) {
        if (n % i == 0)
            return false ;
    }
    return true ;
}
// Primes counter in [a , b )
int primes_count(int a, int b)
{
    int ret = 0;
    for (int i = a; i < b; i++)
        if (is_prime(i) != 0)
            ret++;
    return ret;
}


typedef struct prime_request
{
    int a, b;
} prime_request ;

void * prime_counter (void *arg)
{

    prime_request req = *(prime_request*)arg;
    int count = primes_count(req.a, req.b);
    total += count;
    free(arg);
    pthread_exit(NULL);
    return (( void *) &total );

}



int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s n m\n", argv[0]);
        return EXIT_FAILURE;
    }
    int n = atoi(argv[1]);
    int m = atoi(argv[2]);

    if (m < 1 || m > n) {
        printf("Error: Invalid value for m.\n");
        return EXIT_FAILURE;
    }
    pthread_t tid[m];
    int periods[m+1];
    periods[0] = 0;
    for (int i = 1; i <= m; i++) {
        periods[i] = periods[i-1] + n/m;

    }
    periods[m] = n;
    for (int i = 0; i < m; i++) {
        prime_request* req = malloc(sizeof(prime_request));
        req->a = periods[i];
        req->b = periods[i+1];
        pthread_create(&tid[i], NULL, prime_counter, req);
    }
    
    for (int i = 0; i < m; i++) {
        pthread_join(tid[i], NULL);
    }

    printf("Number of primes in the range [0, %d): %d\n", n, total);
    return EXIT_SUCCESS;
}
