#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/inotify.h>

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


void monitor_directory(const char* path) {
    int inotify_fd = inotify_init();
    if (inotify_fd == -1) {
        perror("inotify_init");
        exit(EXIT_FAILURE);
    }

    int watch_desc = inotify_add_watch(inotify_fd, path, IN_ACCESS | IN_MODIFY | IN_CREATE | IN_DELETE | IN_OPEN);
    if (watch_desc == -1) {
        perror("inotify_add_watch");
        exit(EXIT_FAILURE);
    }

    char buf[4096];
    ssize_t num_read;
    while (1) {
        num_read = read(inotify_fd, buf, sizeof(buf));
        if (num_read == 0) {
            fprintf(stderr, "No events\n");
        }
        if (num_read == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }

        printf("File change detected\n");
        print_all_stat_info(path);
    }

    close(inotify_fd);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <watched_directory>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    signal(SIGINT, handle_sigint);

    print_all_stat_info(argv[1]);
	
    while (1) {
    	monitor_directory(argv[1]);
        sleep(1);
    }

    return 0;
}

