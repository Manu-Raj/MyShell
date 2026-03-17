# MyShell

MyShell is a lightweight, modular Unix-like command-line interpreter
written in C. It demonstrates core operating system concepts such as
process creation, program execution, and command parsing, while adhering
closely to standard UNIX shell semantics.

------------------------------------------------------------------------

## Platform Requirements

This project targets Unix-like environments only.

### Supported

-   Linux (recommended)
-   macOS
-   Windows via Windows Subsystem for Linux (WSL)

### Not Supported

-   Native Windows Command Prompt (CMD)
-   PowerShell

------------------------------------------------------------------------

## Key Features

### Core Execution Model

-   Process creation using `fork()`
-   Program execution using `execve()`
-   Process synchronization via `waitpid()`

### Command Resolution

-   PATH-based command lookup using `execve()`
-   No use of `access()` pre-checks (avoids TOCTOU race conditions)
-   Accurate error reporting (e.g., permission denied vs command not
    found)

------------------------------------------------------------------------

## Built-in Commands

| Command        | Description                                   | Usage Examples        |
|----------------|-----------------------------------------------|----------------------|
| `cd`           | Change current directory                      | `cd`, `cd ~`, `cd -` |
| `pwd`          | Print current working directory               | `pwd`                |
| `echo`         | Print arguments to standard output            | `echo Hello World`   |
| `env`          | Display environment variables                 | `env`                |
| `history`      | Show command history (GNU Readline)           | `history`            |
| `clear`, `cls` | Clear the terminal screen                     | `clear`              |
| `custom`       | Customize the shell prompt style              | `custom`             |
| `help`         | Display usage guide for built-in commands     | `help`               |
| `about`        | Show information about MyShell                | `about`              |
| `exit`, `quit` | Terminate the shell session                   | `exit`               |

------------------------------------------------------------------------

## Architecture

    src/
    ├── main.c              # Main loop (read → parse → execute)
    ├── input_parser.c      # Tokenization
    ├── builtin_handler.c   # Built-in dispatch
    ├── builtins.c          # Built-in implementations
    ├── executor.c          # Process execution logic
    include/
    └── myshell.h

### Execution Flow

    readline → parse_input → shell_builts
        → builtin execution (no fork)
        → external execution (fork → execve → waitpid)

------------------------------------------------------------------------

## Dependencies

### Ubuntu / Debian

``` bash
sudo apt update
sudo apt install build-essential libreadline-dev
```

### Arch Linux

``` bash
sudo pacman -S base-devel readline
```

### macOS (Homebrew)

``` bash
brew install readline
```

------------------------------------------------------------------------

## Build and Run

### Clone the repository

``` bash
git clone https://github.com/yourusername/myshell.git
cd myshell
```

### Build

``` bash
make
```

### Run

``` bash
./myshell
```

### Clean

``` bash
make clean
```

------------------------------------------------------------------------

## Example

``` bash
[myshell]>> pwd
/home/user

[myshell]>> echo Hello World
Hello World

[myshell]>> ls
file1.c  file2.txt
```

------------------------------------------------------------------------

## Design Highlights

-   Direct use of `execve()` for correct UNIX behavior
-   Avoidance of race conditions in command execution
-   Modular and extensible architecture
-   Function pointer-based built-in command dispatch
-   Clear separation between parsing, execution, and command logic

------------------------------------------------------------------------

## Author

Manu Raj

------------------------------------------------------------------------

