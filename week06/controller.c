#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define PID_FILE "/var/run/agent.pid"

int main() {
    FILE *fp = fopen(PID_FILE, "r");
    if (fp == NULL) {
        perror("Error opening PID file");
        exit(1);
    }
    char pid_str[16];
    fgets(pid_str, sizeof(pid_str), fp);
    pid_t pid = atoi(pid_str);
    fclose(fp);

    kill(pid, SIGUSR1);
    sleep(1);
    kill(pid, SIGUSR2);

    return 0;
}
