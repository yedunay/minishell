# Minishell

Minishell is a lightweight Unix shell emulator written in C. It aims to provide users with a basic command-line interface resembling a typical Unix shell environment. The project serves as both a learning tool for understanding the inner workings of operating systems and shell programming, as well as a practical utility for executing basic commands, managing processes, and navigating the file system.

## Features

### 1. Basic Command Execution

Minishell allows users to execute a variety of commands commonly found in Unix-like operating systems. Users can execute both built-in commands (e.g., `cd`, `exit`) and external commands (e.g., `ls`, `grep`) supported by the underlying system.

### 2. Input/Output Redirection

Users can redirect standard input and output streams to and from files using redirection operators (`>`, `<`). This feature enables users to manipulate file content and perform various I/O operations directly from the command line.

### 3. Pipelines

Minishell supports command pipelines, allowing users to chain multiple commands together, where the output of one command serves as the input to the next. This feature enables users to perform complex data processing tasks by combining simple commands in a sequential manner.

### 4. Environment Variable Manipulation

Users can manipulate environment variables within Minishell, including setting new variables, modifying existing ones, and removing variables from the environment. This feature provides users with control over the shell environment and allows for customization according to their preferences.

### 5. Signal Handling

Minishell incorporates signal handling mechanisms to manage signals sent by the operating system or user processes. Signal handling ensures proper termination of processes, handling of interrupts, and graceful shutdown of the shell when necessary.

## Getting Started

### Prerequisites

Before using Minishell, ensure that you have the following prerequisites installed:

- C compiler (e.g., GCC)
- Unix-like operating system (e.g., Linux, macOS)

### Installation

1. Clone the Minishell repository to your local machine:

   ```bash
   git clone https://github.com/yedunay/minishell.git
   ```

2. Navigate to the project directory:

   ```bash
   cd minishell
   ```

3. Compile the source code:

   ```bash
   make
   ```

### Usage

To start Minishell, run the compiled binary:

```bash
./minishell
```

Once launched, you'll be greeted with a command prompt where you can enter commands and interact with Minishell.

### Example Commands

- Execute a command:

  ```bash
  ls -l
  ```

- Redirect output to a file:

  ```bash
  echo "Hello, world!" > output.txt
  ```

- Pipe commands:

  ```bash
  ls -l | grep "pattern"
  ```

- Manipulate environment variables:

  ```bash
  export MY_VAR=value
  ```

- Exit Minishell:

  ```bash
  exit
  ```
```
