#include "myshell.h"

// Function definitions
void shell_loop(char **);
int readline(char *, size_t, FILE *);
int shell_builts(char **, char **, char *);

int readline(char *buf, size_t size, FILE *stream)
{
    int c;
    size_t i = 0;

    if (buf == NULL || size == 0 || stream == NULL)
        return -1;
    while ((c = fgetc(stream)) != EOF && c != '\n')
    {
        if (i < size - 1)
        {
            buf[i++] = c;
        }
    }
    if (c == '\n')
    {
        if (i < size - 1)
            buf[i++] = c;
    }

    buf[i] = '\0';
    if (c == EOF && i == 0)
        return -1;

    return (int)i;
}

void shell_loop(char **env)
{

    char input[MAX_INPUT];
    size_t input_size = sizeof(input);

    char *initial_directory = getcwd(NULL, 0);
    char *username = getenv("USERNAME");
    char **args;

    while (1)
    {
        printf("[myshell]>> ");

        if (readline(input, input_size, stdin) == -1)
            break;

        args = parse_input(input);

        if (args[0] != NULL)
        {
            shell_builts(args, env, initial_directory);
        }

        free_tokens(args);
    }
}

//  main
int main(int argc, char **argv, char **env)
{
    (void)argc;
    (void)argv;

    command_clear(NULL, NULL);
    shell_loop(env);

    return 0;
}