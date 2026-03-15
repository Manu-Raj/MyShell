#include "myshell.h"

extern builtin_cmd command_table[];

int command_exit(char **args, char **env)
{
    (void)args;
    (void)env;
    exit(EXIT_SUCCESS);
}

int command_cd(char **args, char **env)
{
    (void)env;
    static char prev_dir[1024] = "";
    char cwd[1024];
    char *target;

    // get current directory
    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        perror("cd");
        return 1;
    }

    // cd or cd ~ → HOME
    if (args[1] == NULL || strcmp(args[1], "~") == 0)
    {
        target = getenv("HOME");

        if (target == NULL)
        {
            printf("cd: HOME not set\n");
            return 1;
        }
    }

    // cd -
    else if (strcmp(args[1], "-") == 0)
    {
        if (prev_dir[0] == '\0')
        {
            printf("cd: OLDPWD not set\n");
            return 1;
        }

        printf("%s\n", prev_dir);
        target = prev_dir;
    }

    // cd directory
    else
    {
        target = args[1];
    }

    // change directory
    if (chdir(target) != 0)
    {
        perror("cd");
        return 1;
    }

    // update previous directory
    strcpy(prev_dir, cwd);

    return 0;
}

int command_clear(char **args, char **env)
{
    (void)args;
    (void)env;
    printf("\033[H\033[J");
    return 0;
}

int command_pwd(char **args, char **env)
{
    (void)args;
    (void)env;

    char *cwd = getcwd(NULL, 0);
    if (cwd)
    {
        printf("%s\n", cwd);
        free(cwd);
    }
    else
    {
        perror("pwd");
    }

    return 0;
}

int command_echo(char **args, char **env)
{
    (void)env;
    int i = 1;

    while (args[i] != NULL)
    {
        printf("%s", args[i]);

        if (args[i + 1] != NULL)
            printf(" ");

        i++;
    }

    printf("\n");

    return 0;
}

int command_env(char **args, char **env)
{
    (void)args;
    if (!env)
        return 1;
    int i = 0;

    while (env[i] != NULL)
    {
        printf("%s\n", env[i]);
        i++;
    }

    return 0;
}

int command_which(char **args, char **env)
{
    (void)args;
    (void)env;
    printf("work to be done\n");
    return 0;
}

int display_help(char **args, char **env)
{
    (void)args;
    (void)env;
    printf(
        "MyShell Built-in Commands:\n"
        "  cd [dir]     Change directory\n"
        "  pwd          Print current directory\n"
        "  echo [text]  Print text\n"
        "  env          Show environment variables\n"
        "  which [cmd]  Locate command in PATH\n"
        "  clear | cls  Clear the shell\n"
        "  help         Display this help\n"
        "  exit | quit  Exit the shell\n");
    return 0;
}