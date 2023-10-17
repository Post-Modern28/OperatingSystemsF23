#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define PID_FILE "/var/run/agent.pid"
#define TEXT_FILE "text.txt"

void sigusr1_handler(int sig) {
    char buffer[1024];
    FILE *fp = fopen(TEXT_FILE, "r");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }
    while (fgets(buffer, sizeof(buffer), fp)) {
        printf("%s", buffer);
    }
    fclose(fp);
}

void sigusr2_handler(int sig) {
    printf("Process terminating...\n");
    exit(0);
}

int main() {

    int fd = open(PID_FILE, O_WRONLY | O_CREAT | O_EXCL, 0644);
    if (fd == -1) {
        perror("Error creating PID file");
        exit(1);
    }
    char pid_str[16];
    sprintf(pid_str, "%d\n", getpid());
    write(fd, pid_str, strlen(pid_str));
    close(fd);

    FILE *fp = fopen(TEXT_FILE, "r");
    if (fp == NULL) {
        perror("Error opening file");
        exit(1);
    }
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), fp)) {
        printf("%s", buffer);
    }
    fclose(fp);

    signal(SIGUSR1, sigusr1_handler);
    signal(SIGUSR2, sigusr2_handler);

    while (1) {
        sleep(1);
    }

    return 0;
}

