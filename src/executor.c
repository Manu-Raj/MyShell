#include "myshell.h"

/*
** Forks and executes a command
*/
int executor(char **args, char **env)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        return 1;
    }

    if (pid == 0)
    {
        /* child process */
        child_process(args, env);
    }
    else
    {
        /* parent process waits */
        if (waitpid(pid, &status, 0) < 0)
        {
            perror("waitpid");
            return 1;
        }

        if (WIFEXITED(status))
            return WEXITSTATUS(status);

        if (WIFSIGNALED(status))
        {
            int sig = WTERMSIG(status);
            printf("Process terminated by signal %d\n", sig);
            return 128 + sig;
        }
    }

    return 0;
}

/*
** Executes command in child
*/
int child_process(char **args, char **env)
{
    char *path_env;
    char *path_copy;
    char *dir;
    char full_path[1024];

    if (!args || !args[0])
        exit(0);

    /* if command contains '/' run directly */
    if (strchr(args[0], '/'))
    {
        execve(args[0], args, env);
        perror(args[0]);
        exit(127);
    }

    /* get PATH */
    path_env = getenv("PATH");
    if (!path_env)
    {
        execve(args[0], args, env);
        perror(args[0]);
        exit(127);
    }

    /* duplicate PATH so strtok can modify */
    path_copy = strdup(path_env);
    if (!path_copy)
    {
        perror("strdup");
        exit(1);
    }

    dir = strtok(path_copy, ":");

    while (dir)
    {
        snprintf(full_path, sizeof(full_path), "%s/%s", dir, args[0]);

        if (access(full_path, X_OK) == 0)
            execve(full_path, args, env);

        dir = strtok(NULL, ":");
    }

    free(path_copy);

    fprintf(stderr, "%s: command not found\n", args[0]);
    exit(127);
}