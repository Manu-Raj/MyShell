# MyShell

A simple Unix-like shell written in C

## Features

-   Execute external programs
-   Basic command parsing
-   Built-in commands (cd, pwd, echo, env, clear, help, exit)
-   Uses fork(), execve(), and waitpid()

## Build

Compile using:

    make

Or manually:

    gcc src/*.c -Iinclude -Wall -Wextra -o myshell

## Run

    ./myshell

## Project Structure

    include/    Header files
    src/        Source code
    Makefile    Build script

