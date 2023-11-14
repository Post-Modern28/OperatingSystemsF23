#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>
#include <dirent.h>

void print_stat_info(const char* path) {
    struct stat fileStat;
    if (stat(path, &fileStat) < 0) {
        perror("stat");
        exit(EXIT_FAILURE);
    }
    printf("File/Directory: %s\n", path);
    printf("Size: %ld bytes\n", fileStat.st_size);
    printf("Inode: %lu\n", fileStat.st_ino);
    printf("Permissions: %o\n", fileStat.st_mode);
    printf("------------------------\n");
}

void print_all_stat_info(const char* path) {
    DIR *dir;
    struct dirent *entry;
    dir = opendir(path);
    if (dir == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG || entry->d_type == DT_DIR) {
            char full_path[PATH_MAX];
            snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
            print_stat_info(full_path);
        }
    }
    closedir(dir);
}

void handle_sigint(int sig) {
    printf("\nReceived SIGINT. Printing stat info before termination...\n");
    print_all_stat_info(".");
    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <watched_directory>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    signal(SIGINT, handle_sigint);

    print_all_stat_info(argv[1]);

    while (1) {
        sleep(5);
    }

    return 0;
}

