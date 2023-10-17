#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#define PID_FILE "/var/run/agent.pid"

int main() {
    FILE *pid_file = fopen("/var/run/agent.pid", "r");
    if (pid_file == NULL) {
        printf("Error: No agent found.\n");
        exit(1);
    }
    int agent_pid;
    fscanf(pid_file, "%d", &agent_pid);
    fclose(pid_file);
    printf("Agent found.\n");

    char command[10];
    while (1) {
        printf("Choose a command {\"read\", \"exit\", \"stop\", \"continue\"}: ");
        scanf("%s", command);
        if (strcmp(command, "read") == 0) {
            kill(agent_pid, SIGUSR1);
        } else if (strcmp(command, "exit") == 0) {
            kill(agent_pid, SIGUSR2);
            exit(0);
        } else if (strcmp(command, "stop") == 0) {
            kill(agent_pid, SIGSTOP);
        } else if (strcmp(command, "continue") == 0) {
            kill(agent_pid, SIGCONT);
        }
    }

    return 0;
}
