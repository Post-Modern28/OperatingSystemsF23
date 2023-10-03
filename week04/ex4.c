#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_ARGS 10

int main() {
    char input[100];
    char *args[MAX_ARGS];
    int background = 0;

    while (1) {
        printf("Enter a command: ");
        fgets(input, sizeof(input), stdin);
        input[strlen(input)-1] = '\0'; 

        if (strcmp(input, "exit") == 0) {
            break;
        }

        int i = 0;
        char *token = strtok(input, " ");
        while (token != NULL && i < MAX_ARGS) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        if (i == 0) {
            continue; 
        }

        if (strcmp(args[i-1], "&") == 0) {
            background = 1;
            args[i-1] = NULL;
        }

        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            execvp(args[0], args);
            perror("execvp");
            exit(EXIT_FAILURE);
        } else {
            if (!background) {
                waitpid(pid, NULL, 0);
            }
        }
    }

    return 0;
}

