#include "myshell.h"

void shell_loop(char **env);
char *shell_format = "[myshell]>> ";

/* Shell main loop */
void shell_loop(char **env)
{
    char *input;
    char **args;

    while (1)
    {
        input = readline(shell_format);

        if (!input)
            break;

        if (input[0] != '\0')
            add_history(input);

        args = parse_input(input);

        if (args && args[0])
            shell_builts(args, env);

        free_tokens(args);
        free(input);
    }
}

/* Program entry point */
int main(int argc, char **argv, char **env)
{
    (void)argc;
    (void)argv;

    command_clear(NULL, NULL);
    shell_loop(env);

    return EXIT_SUCCESS;
}