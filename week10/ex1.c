#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

void find_all_hlinks(const char* source) {
    struct stat fileStat;
    if (lstat(source, &fileStat) < 0) {
        perror("lstat");
        exit(EXIT_FAILURE);
    }
    ino_t inode = fileStat.st_ino;

    DIR *dir;
    struct dirent *entry;
    dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {
            struct stat st;
            if (lstat(entry->d_name, &st) < 0) {
                perror("lstat");
                exit(EXIT_FAILURE);
            }
            if (st.st_ino == inode) {
                char resolved_path[PATH_MAX];
                if (realpath(entry->d_name, resolved_path) == NULL) {
                    perror("realpath");
                    exit(EXIT_FAILURE);
                }
                printf("Inode: %lu, Path: %s\n", st.st_ino, resolved_path);
            }
        }
    }
    closedir(dir);
}

void unlink_all(const char* source) {
    struct stat fileStat;
    if (lstat(source, &fileStat) < 0) {
        perror("lstat");
        exit(EXIT_FAILURE);
    }
    ino_t inode = fileStat.st_ino;

    DIR *dir;
    struct dirent *entry;
    dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {
            struct stat st;
            if (lstat(entry->d_name, &st) < 0) {
                perror("lstat");
                exit(EXIT_FAILURE);
            }
            if (st.st_ino == inode && strcmp(entry->d_name, source) != 0) {
                if (unlink(entry->d_name) < 0) {
                    perror("unlink");
                    exit(EXIT_FAILURE);
                }
            }
        }
    }
    closedir(dir);
    printf("Last hard link: %s\n", source);
}

void create_sym_link(const char* source, const char* link) {
    if (symlink(source, link) < 0) {
        perror("symlink");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <watched_directory>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    chdir(argv[1]);

    FILE *fp = fopen("myfile1.txt", "w");
    fprintf(fp, "Hello world.");
    fclose(fp);

    link("myfile1.txt", "myfile11.txt");
    link("myfile1.txt", "myfile12.txt");

    find_all_hlinks("myfile1.txt");

    rename("myfile1.txt", "/tmp/myfile1.txt");


    create_sym_link("/tmp/myfile1.txt", "myfile13.txt");


    unlink_all("myfile11.txt");

    return 0;
}
