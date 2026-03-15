#include "myshell.h"

extern builtin_cmd command_table[];

int command_exit(char **args, char **env)
{
    exit(EXIT_SUCCESS);
    return 0;
}

int command_cd(char **args, char **env)
{
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
    printf("\033[H\033[J");
    return 0;
}

int command_pwd(char **args, char **env)
{
    char cwd[1024];

    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("%s\n", cwd);
    }
    else
    {
        perror("pwd");
    }

    return 0;
}

int command_echo(char **args, char **env)
{
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
  printf("work to be done\n");
  return 0;
}

int display_help(char **args, char **env)
{
    printf("MyShell Built-in Commands:\n");
    printf("  cd [dir]     Change directory\n");
    printf("  pwd          Print current directory\n");
    printf("  echo [text]  Print text\n");
    printf("  env          Show environment variables\n");
    printf("  which [cmd]  Locate command in PATH\n");
    printf("  clear | cls  Clear the shell\n");
    printf("  help         Display this help\n");
    printf("  exit | quit  Exit the shell\n");

    return 0;
}