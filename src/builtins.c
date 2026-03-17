#include "myshell.h"

extern builtin_cmd command_table[];
extern char *shell_format;

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

int command_history(char **args, char **env)
{
    (void)args;
    (void)env;

    HIST_ENTRY **hist_list = history_list();

    if (!hist_list)
        return 0;

    for (int i = 0; hist_list[i]; i++)
    {
        printf("%d  %s\n", i + history_base, hist_list[i]->line);
    }

    return 0;
}

int command_custom(char **args, char **env)
{
    (void)args;
    (void)env;

    char buf[16];
    int choice;

    char cwd[PATH_MAX];
    char *host;
    char *user;

#ifndef _WIN32
    static char hostbuf[64];
#endif

    static char prompt[PATH_MAX + 128];

    printf(
        "MyShell Custom prompt styles:\n\n"
        " 1   [myshell]>>\n"
        " 2   user@host$\n"
        " 3   user@host:~/dir$\n"
        " 4   [user@host]$\n"
        " 5   user@host ➜ ~/dir $\n"
        " 6   [myshell|~/dir]$\n"
        " 7   ┌─ user@host ~/dir\n"
        "     └─$\n"
        " 8   ╭─ user@host ~/dir\n"
        "     ╰─$\n");

    printf("\nSelect prompt style (1-8): ");

    if (!fgets(buf, sizeof(buf), stdin))
        return 1;

    choice = atoi(buf);

    if (choice < 1 || choice > 8)
    {
        printf("Invalid selection.\n");
        return 1;
    }

    /* Fetch system information */

#ifdef _WIN32
    user = getenv("USERNAME");
    host = getenv("COMPUTERNAME");
#else
    user = getenv("USER");
    gethostname(hostbuf, sizeof(hostbuf));
    host = hostbuf;
#endif

    if (!user)
        user = "user";

    if (!host)
        host = "host";

    if (getcwd(cwd, sizeof(cwd)) == NULL)
        strcpy(cwd, "?");

    /* Build prompt */

    switch (choice)
    {
    case 1:
        snprintf(prompt, sizeof(prompt), "[myshell]>> ");
        break;

    case 2:
        snprintf(prompt, sizeof(prompt), "%s@%s$ ", user, host);
        break;

    case 3:
        snprintf(prompt, sizeof(prompt), "%s@%s:%s$ ", user, host, cwd);
        break;

    case 4:
        snprintf(prompt, sizeof(prompt), "[%s@%s]$ ", user, host);
        break;

    case 5:
        snprintf(prompt, sizeof(prompt), "%s@%s ➜ %s $ ", user, host, cwd);
        break;

    case 6:
        snprintf(prompt, sizeof(prompt), "[myshell|%s]$ ", cwd);
        break;

    case 7:
        snprintf(prompt, sizeof(prompt),
                 "┌─ %s@%s %s\n└─$ ",
                 user, host, cwd);
        break;

    case 8:
        snprintf(prompt, sizeof(prompt),
                 "╭─ %s@%s %s\n╰─$ ",
                 user, host, cwd);
        break;
    }

    shell_format = prompt;

    printf("Prompt updated.\n");

    return 0;
}

int command_about(char **args, char **env)
{
    (void)args;
    (void)env;
    printf(
        "---------------------------------------------------\n"
        "                     MyShell\n"
        "---------------------------------------------------\n"
        "A minimal Unix-like command line shell written in C.\n\n"
        "Core Features:\n"
        "  • Process creation using fork()\n"
        "  • Program execution via execve()\n"
        "  • Process synchronization using waitpid()\n"
        "  • PATH-based command resolution (no access() pre-checks)\n"
        "  • Built-in command dispatch using function pointers\n\n"
        "Built-in Commands:\n"
        "  cd, pwd, echo, env, history, clear, help, exit\n\n"
        "Design Highlights:\n"
        "  • Modular architecture (parser, executor, builtins)\n"
        "  • Correct UNIX execution model (no TOCTOU issues)\n"
        "  • Dynamic token parsing and memory management\n\n"
        "Developed by: Manu Raj\n"
        "---------------------------------------------------\n");
    return 0;
}

int display_help(char **args, char **env)
{
    (void)args;
    (void)env;
    printf(
        "\nMyShell - Built-in Commands\n"
        "------------------------------------------------------\n"
        "  cd [dir]       Change current directory\n"
        "                 • cd        → go to HOME\n"
        "                 • cd -      → switch to previous dir\n\n"
        "  pwd            Print current working directory\n\n"
        "  echo [text]    Print arguments to standard output\n\n"
        "  env            Display environment variables\n\n"
        "  which [cmd]    Locate command in PATH (planned/partial)\n\n"
        "  history        Show command history (readline)\n\n"
        "  clear | cls    Clear the terminal screen\n\n"
        "  custom         Change shell prompt style\n\n"
        "  about          Display information about MyShell\n\n"
        "  help           Show this help message\n\n"
        "  exit | quit    Exit the shell\n"
        "------------------------------------------------------\n"
        "Execution Notes:\n"
        "  • External commands are resolved via PATH\n"
        "  • Uses execve() directly (no access() pre-check)\n"
        "  • Reports accurate errors (e.g., permission denied)\n"
        "------------------------------------------------------\n");
    return 0;
}