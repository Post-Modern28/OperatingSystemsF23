#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_MSG_SIZE 1024

int main() {
    int fd[2];
    pid_t pid;

    if (pipe(fd) == -1) {
        return 1;
    }

    pid = fork();

    if (pid == -1) {
        return 1;
    }

    if (pid == 0) { 
        close(fd[1]); 

        char msg[MAX_MSG_SIZE];
        ssize_t num_bytes = read(fd[0], msg, MAX_MSG_SIZE);
        if (num_bytes == -1) {
			return 2;           
        }
        printf("%s", msg);

        close(fd[0]);
        exit(EXIT_SUCCESS);
    } else {
        close(fd[0]); 

        char msg[MAX_MSG_SIZE];
        printf("Enter message: ");
        fgets(msg, MAX_MSG_SIZE, stdin);

        ssize_t num_bytes = write(fd[1], msg, strlen(msg));
        if (num_bytes == -1) {
            return 2;
        }

        close(fd[1]); 
        exit(EXIT_SUCCESS);
    }
}
