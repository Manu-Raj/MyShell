#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INPUT 1024
#define MAX_ARGS 64

int main() {
    char input[MAX_INPUT];
    char *args[MAX_ARGS];

    while (1) {
        printf("myshell> ");
        fgets(input, MAX_INPUT, stdin);

        // Remove newline
        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "exit") == 0) {
            break;
        }

        // Parse input into arguments
        int i = 0;
        args[i] = strtok(input, " ");
        while (args[i] != NULL && i < MAX_ARGS - 1) {
            i++;
            args[i] = strtok(NULL, " ");
        }

        // Create child process
        pid_t pid = fork();

        if (pid == 0) {
            execvp(args[0], args);
            perror("Command failed");
            exit(1);
        } 
        else if (pid > 0) {
            wait(NULL);
        } 
        else {
            perror("Fork failed");
        }
    }

    return 0;
}