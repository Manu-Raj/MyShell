#include "myshell.h"

builtin_cmd command_table[] = {
    {"cd", command_cd},
    {"pwd", command_pwd},
    {"echo", command_echo},
    {"clear", command_clear},
    {"cls", command_clear},
    {"env", command_env},
    {"which", command_which},
    {"help", display_help},
    {"about", command_about},
    {"custom", command_custom},
    {"exit", command_exit},
    {"quit", command_exit},
    {NULL, NULL}};

int shell_builts(char **args, char **env, char *initial_directory)
{
    (void)initial_directory;

    for (int i = 0; command_table[i].name != NULL; i++)
    {
        if (strcmp(args[0], command_table[i].name) == 0)
        {
            return command_table[i].func(args, env);
        }
    }

    // If command not found go to the executor
    return executor(args, env);
}
