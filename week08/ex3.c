#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <unistd.h>

#define MB 1048576

int main() {
    struct rusage usage;
    void* ptr;
    int i;

    for(i = 0; i < 10; i++) {
        ptr = malloc(10 * MB);
        memset(ptr, 0, 10 * MB);
        getrusage(RUSAGE_SELF, &usage);
        printf("Memory usage: %ld\n", usage.ru_maxrss);
        sleep(1);
    }

    return 0;
}
