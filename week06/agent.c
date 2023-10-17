#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>


void sig_handler(int sig) {
    if (sig == SIGUSR1) {
        FILE *file = fopen("text.txt", "r");
        if (file == NULL) {
            printf("Error: Unable to open text file.\n");
            exit(1);
        }
        char buffer[256];
        while (fgets(buffer, sizeof(buffer), file)) {
            printf("%s", buffer);
        }
        fclose(file);
    } else if (sig == SIGUSR2) {
        printf("Process terminating...\n");
        exit(0);
    }
}

int main() {
    // Write PID to file
    FILE *pid_file = fopen("/var/run/agent.pid", "w");
    if (pid_file == NULL) {
        printf("Error: Unable to create PID file.\n");
        exit(1);
    }
    fprintf(pid_file, "%d", getpid());
    fclose(pid_file);

    // Set signal handlers
    signal(SIGUSR1, sig_handler);
    signal(SIGUSR2, sig_handler);

    FILE *file = fopen("text.txt", "r");
    if (file == NULL) {
        printf("Error: Unable to open text file.\n");
        exit(1);
    }
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }
    fclose(file);
    while (1) {
        sleep(1);
    }

    return 0;
}
