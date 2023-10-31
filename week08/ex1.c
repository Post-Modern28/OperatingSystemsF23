#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>

int main() {
    FILE *fp = fopen("/tmp/ex1.pid", "w");
    fprintf(fp, "%d", getpid());
    fclose(fp);
    int fd = open("/dev/urandom", O_RDONLY);
    char password[9];
    printf("Reading password");
    read(fd, password, 8);
    close(fd);
    printf("Closed file");
    password[8] = '\0';
    for (int i = 0; i < 8; i++) {
        password[i] = (password[i] % 94) + 33; 
    }
    char *mapped_memory;
    mapped_memory = mmap(NULL, sizeof(password)+5, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    if (mapped_memory == MAP_FAILED) {
        printf("Error: mmap failed\n");
        exit(1);
    }
    sprintf(mapped_memory, "pass:%s", password);
    
    while (1) {
        sleep(1);
    }

    return 0;
}
