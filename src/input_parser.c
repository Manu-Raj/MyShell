#include "myshell.h"
#include <ctype.h>
#include <string.h>

char **parse_input(char *input)
{
    size_t buffer_size = MAX_INPUT;
    char **tokens = malloc(buffer_size * sizeof(char *));
    size_t position = 0;
    size_t i = 0;

    if (!tokens)
    {
        perror("malloc");
        exit(1);
    }

    while (input[i])
    {
        // Skip whitespace
        while (input[i] && isspace(input[i]))
            i++;

        if (!input[i])
            break;

        char *start = &input[i];
        size_t token_length = 0;

        // Find token length
        while (input[i] && !isspace(input[i]))
        {
            token_length++;
            i++;
        }

        // Resize tokens array if needed
        if (position >= buffer_size - 1)
        {
            buffer_size *= 2;
            char **tmp = realloc(tokens, buffer_size * sizeof(char *));
            if (!tmp)
            {
                perror("realloc");
                free(tokens);
                exit(1);
            }
            tokens = tmp;
        }

        // Allocate memory for token
        tokens[position] = malloc(token_length + 1);

        if (!tokens[position])
        {
            perror("malloc");
            exit(1);
        }

        memcpy(tokens[position], start, token_length);
        tokens[position][token_length] = '\0';

        position++;
    }

    tokens[position] = NULL;
    return tokens;
}

// Free allocated tokens
void free_tokens(char **tokens)
{
    if (!tokens)
        return;

    for (size_t i = 0; tokens[i]; i++)
        free(tokens[i]);

    free(tokens);
}