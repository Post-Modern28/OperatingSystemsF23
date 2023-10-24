
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

#define MAX_LINE_LENGTH 1024
#define MAX_FILE_SIZE (500 * 1024 * 1024)

void generate_file() {
    int fd = open("/dev/random", O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    FILE *fp = fopen("text.txt", "w");
    if (fp == NULL) {
        perror("fopen");
        exit(1);
    }

    char line[MAX_LINE_LENGTH];
    int count = 0;
    while (count < MAX_FILE_SIZE) {
        char c;
        if (read(fd, &c, 1) == -1) {
            perror("read");
            exit(1);
        }
        if (isprint(c)) {
            line[count % MAX_LINE_LENGTH] = c;
            count++;
            if (count % MAX_LINE_LENGTH == 0) {
                line[MAX_LINE_LENGTH] = '\0';
                fprintf(fp, "%s\n", line);
            }
        }
    }

    fclose(fp);
    close(fd);
}

void process_chunk(char *chunk, size_t size, size_t *count) {
    for (size_t i = 0; i < size; i++) {
        if (isupper(chunk[i])) {
            chunk[i] = tolower(chunk[i]);
            (*count)++;
        }
    }
}

int main() {
    generate_file();

    long page_size = sysconf(_SC_PAGESIZE);
    size_t chunk_size = page_size * 1024;
    int fd = open("text.txt", O_RDWR);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    size_t file_size = lseek(fd, 0, SEEK_END);
    char *file = mmap(NULL, file_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (file == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    size_t count = 0;
    for (size_t i = 0; i < file_size; i += chunk_size) {
        size_t size = (i + chunk_size <= file_size) ? chunk_size : file_size - i;
        char *chunk = file + i;
        process_chunk(chunk, size, &count);
    }

    printf("Total capital letters: %zu\n", count);

    for (size_t i = 0; i < file_size; i++) {
        if (isupper(file[i])) {
            file[i] = tolower(file[i]);
        }
    }

    if (munmap(file, file_size) == -1) {
        perror("munmap");
        exit(1);
    }

    close(fd);

    return 0;
}
