#include "myshell.h"


void shell_loop(char**);
int getline(char *, size_t, FILE *);



int getline(char *buf, size_t size, FILE *stream){
    int c;
    size_t i = 0;

    if (buf == NULL || size == 0 || stream == NULL)
        return -1;
    while ((c = fgetc(stream)) != EOF && c != '\n') {
        if (i < size - 1) {
            buf[i++] = c;
        }
    }
    if (c == '\n') {
        if (i < size - 1)
            buf[i++] = c;
    }

    buf[i] = '\0';
    if (c == EOF && i == 0)
        return -1;

    return (int)i;
}


void shell_loop(char** env){

    char input[MAX_INPUT];
    size_t input_size = sizeof(input);


    char** args;

    while (1)
    {
        printf("myshell>> ");
        if(getline(input,input_size,stdin)==-1){
            break;
        }

        //printf("Input:%s",input);
        args=parse_input(input);


    }
    
}

int main(int argc, char** argv, char** env){
    (void)argc;
    (void)argv;

    shell_loop(env);
    
    return 0;
}