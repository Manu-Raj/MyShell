# MyShell

**MyShell** is a lightweight Unix-like command line shell written in
**C**.\
It provides a minimal interactive environment capable of executing
external programs and handling several built-in commands while
demonstrating core operating system concepts.

MyShell focuses on clarity and simplicity while maintaining a structure
similar to traditional Unix shells.

------------------------------------------------------------------------

## Features

-   Execution of external programs
-   Built-in command support
-   Basic command parsing
-   Command history and interactive input via **GNU Readline**
-   Customizable shell prompt styles
-   UTF-8 prompt rendering
-   Modular project structure

------------------------------------------------------------------------

## Dependencies

MyShell requires the **GNU Readline library** for command input editing
and history support.

Install the development package before building.

### Ubuntu / Debian

``` bash
sudo apt install libreadline-dev
```


------------------------------------------------------------------------
## Built-in Commands

| Command | Description |
|--------|-------------|
| `cd [dir]` | Change the current directory |
| `pwd` | Display the current working directory |
| `echo [text]` | Print text to the terminal |
| `env` | Show environment variables |
| `which [cmd]` | Locate a command in the system PATH |
| `clear` / `cls` | Clear the terminal screen |
| `custom` | Select a custom shell prompt style |
| `about` | Display information about MyShell |
| `help` | Display built-in command help |
| `exit` / `quit` | Exit the shell |

------------------------------------------------------------------------

## Platform Support

MyShell is designed for **Unix-like environments** and depends on POSIX
system calls such as:

-   `fork()`
-   `execve()`
-   `waitpid()`

### Windows

Windows users should run MyShell using **Windows Subsystem for Linux
(WSL)** to ensure compatibility.

Install WSL if needed:

``` powershell
wsl --install
```

Then build and run MyShell inside the Linux environment.

------------------------------------------------------------------------

## Build Instructions

### Using Make

``` bash
make
```

### Manual Compilation

``` bash
gcc src/*.c -Iinclude -Wall -Wextra -lreadline -lncurses -o myshell
```

------------------------------------------------------------------------

## Running

``` bash
./myshell
```

------------------------------------------------------------------------

## Project Structure

    include/        Header files
    src/            Source files
    Makefile        Build configuration
    README.md       Project documentation

------------------------------------------------------------------------

## Author

**Maniish Rajendran**
