#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

#ifndef MAX_INPUT
#define MAX_INPUT 1024
#endif

// Shell format
extern char *shell_format;

// input_parser
char **parse_input(char *input);
void free_tokens(char **tokens);


// builtin_handler
typedef struct
{
    char *name;
    int (*func)(char **args, char **env);
} builtin_cmd;

int shell_builts(char **args, char **env);


// builtins
int command_cd(char **args, char **env);
int command_pwd(char **args, char **env);
int command_echo(char **args, char **env);
int command_env(char **args, char **env);
int command_about(char **args, char **env);
int command_custom(char **args, char **env);
int command_which(char **args, char **env);
int command_clear(char **args, char **env);

char **command_setenv(char **args, char **env);
char **command_unsetenv(char **args, char **env);

int display_help(char **args, char **env);
int command_exit(char **args, char **env);


// executor
int executor(char **args, char **env);
int child_process(char **args, char **env);