# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>
// primality test ( from ex3 )

pthread_mutex_t global_lock =
        PTHREAD_MUTEX_INITIALIZER ;

int currentNumber = 0;
int countOfPrimes = 0;
int n = 0;

int get_number_to_check (){
	pthread_mutex_lock(&global_lock);
    int candidate = currentNumber;
    if (currentNumber != n)
        currentNumber++;
    pthread_mutex_unlock(&global_lock);
    return candidate;
}

bool is_prime(int x){
    if (x <= 1) return false;
    int i = 2;
    for (; i * i <= x; i++) {
        if (x % i == 0)
            return false;
    }
    return true;
}

void increment_primes (){
	pthread_mutex_lock(&global_lock);
    countOfPrimes++;
    pthread_mutex_unlock(&global_lock);
}
void * check_primes (void * arg){
    while(1) {
        int num = get_number_to_check();
        if (num == n){
            pthread_exit(NULL);
        }
        if (is_prime(num))
            increment_primes();
    }
}


int main(int argc, char *argv[]){
    n = atoi(argv[1]);
    int m = atoi(argv[2]);
    pthread_t tid[m];
    for (int i = 0; i < m; i++){
        pthread_create(&tid[i], NULL, &check_primes, &currentNumber);
    }
    for (int i = 0; i < m; i++) {
        pthread_join(tid[i], NULL);
    }
    pthread_mutex_destroy(&global_lock);
    printf("Number of primes in the range [0, %d): %d\n", n, countOfPrimes);
    return EXIT_SUCCESS;
}
