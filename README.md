# 🐚 Minishell

*As beautiful as a shell.* **Minishell** is one of the most significant milestone projects in the 1337 (42 Network) core curriculum. The objective is simple to explain but complex to execute: recreate a working, POSIX-compliant shell from scratch in C, mirroring the core behaviors of `bash`.

---

## 📖 About The Project

Before diving into complex automation pipelines or high-level infrastructure configuration, you must understand exactly how a command-line interface interprets human input and translates it into system processes. 

Minishell requires building a complete interpreter. This means handling everything from lexical analysis (breaking strings into tokens) and parsing (building abstract syntax trees or command tables) to execution (forking processes, piping file descriptors, and managing environment variables).

### 🎯 Core Objectives
* **Lexing & Parsing:** Handle quotes (`'` and `"`), environment variable expansion (`$VAR`), and identify operators (`|`, `<`, `>`, `<<`, `>>`).
* **Process Management:** Deep mastery of `fork()`, `execve()`, `waitpid()`, and preventing zombie processes.
* **Inter-Process Communication:** Routing standard input and output through pipes (`|`) and managing multiple file descriptors simultaneously without leaks.
* **Signal Handling:** Catching and properly routing OS signals (`SIGINT`, `SIGQUIT`) so the shell behaves exactly like bash when you press `Ctrl+C`, `Ctrl+D`, or `Ctrl+\\`.

---

## ✨ Features

This shell supports a robust set of standard features:

### ⚙️ Core Mechanics
* **Prompt:** Displays a custom prompt while waiting for a new command.
* **History:** Maintains a working command history.
* **Path Resolution:** Automatically searches the `$PATH` environment variable to locate and execute system binaries (e.g., `ls`, `cat`, `grep`).
* **Exit Status:** Accurately expands `$?` to the exit status of the most recently executed foreground pipeline.

### 🔀 Redirections & Pipes
* `<` : Redirect input.
* `>` : Redirect output (truncate).
* `>>` : Redirect output (append).
* `<<` : Heredoc (reads input from the current source until a delimiter is seen).
* `|` : Connects the output of one command to the input of the next.

### 🛠️ Built-in Commands
Minishell implements the following built-ins exactly as they behave in bash:
* `echo` (with the `-n` option).
* `cd` (with only a relative or absolute path).
* `pwd` (prints the current working directory).
* `export` (adds or updates environment variables).
* `unset` (removes environment variables).
* `env` (prints the current environment).
* `exit` (exits the shell, optionally with a specific exit code).

---

## 🏗️ Architecture (Under the Hood)

1. **Readline:** Captures the raw user input.
2. **Lexer/Tokenizer:** Splits the raw string into meaningful tokens (words, pipes, redirections), respecting the strict rules of single and double quotes.
3. **Expander:** Replaces environment variables (e.g., `$USER`) with their actual values from the stored environment linked list.
4. **Parser:** Organizes the tokens into a structured command table (or AST), grouping commands with their specific arguments and I/O redirections.
5. **Executor:** Iterates through the command table, sets up necessary pipes/redirections, forks child processes, and executes the binaries or built-ins.

---

## 🛠️ Getting Started

### Prerequisites
* A standard C compiler (`cc`, `gcc`, or `clang`)
* `make` utility
* GNU `readline` library (usually installed via `dnf install readline-devel` on Fedora, or `brew install readline` on macOS)

### Installation & Compilation

1. Clone the repository:
   ```bash
   git clone git@github.com:yuuryyy/Minishell_42.git
   cd Minishell_42
   ```

2. Compile the shell:
   ```bash
   make
   ```
   This will generate the `minishell` executable.

### Makefile Rules
* `make` / `make all`: Compiles the shell.
* `make clean`: Removes the compiled `.o` object files.
* `make fclean`: Removes the object files and the executable.
* `make re`: Runs `fclean` followed by `all`.

---

## 💻 Usage

Launch the shell by simply running the executable:

```bash
./minishell
```

Once inside, you can use it just like your regular terminal:
```bash
minishell$ echo "Hello World" | grep Hello > output.txt
minishell$ cat output.txt
Hello World
minishell$ exit
```

---
*Developed by Youssra Chagri and Kaoutar Afkhar at 1337 (UM6P).*
